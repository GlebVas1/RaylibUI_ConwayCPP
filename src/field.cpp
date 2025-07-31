#include "field.h"

Field::Field() :
    buffer_0_(static_cast<uint8_t*>(malloc(field_width_ * field_height_))),
    buffer_1_(static_cast<uint8_t*>(malloc(field_width_ * field_height_))),
    color_buffer_(static_cast<uint8_t*>(malloc(field_width_ * field_height_ * 4))),
    controller_(Controller::GetInstance())
{ }

Field::~Field() {
    free(buffer_0_);
    free(buffer_1_);
    free(color_buffer_);
}

uint8_t* Field::GetReadBuffer() {
    return read_buffer_ == 0 ? buffer_0_ : buffer_1_;
}

uint8_t* Field::GetWriteBuffer() {
    return read_buffer_ == 1 ? buffer_0_ : buffer_1_;
}

void Field::SwitchBuffer() {
  read_buffer_ = 1 - read_buffer_;
}
size_t Field::BufferIndex(size_t x, size_t y) {
    return x * field_width_ + y;
}

uint8_t* Field::GetColorBuffer() {
    return color_buffer_;
}

void Field::ReinitializeBuffer() {
    free(buffer_0_);
    free(buffer_1_);
    buffer_0_ = static_cast<uint8_t*>(malloc(field_width_ * field_height_));
    buffer_1_ = static_cast<uint8_t*>(malloc(field_width_ * field_height_));
}

void Field::ReinitializeColorBuffer() {
    free(color_buffer_);
    color_buffer_ = static_cast<uint8_t*>(malloc(field_width_ * field_height_ * 4));
}

void Field::SetPixel(size_t x, size_t y, uint8_t val, uint8_t* buffer) {
    buffer[BufferIndex(x, y)] = val;
}

void Field::SetPixelColor(size_t x, size_t y,  uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    size_t index = BufferIndex(x, y);
    color_buffer_[4 * index] = r;
    color_buffer_[4 * index + 1] = g;
    color_buffer_[4 * index + 2] = b;
    color_buffer_[4 * index + 3] = a;
}

uint8_t Field::GetPixel(size_t x, size_t y, uint8_t* buffer) {
    return buffer[BufferIndex(x, y)];
}


void Field::UpdatePixel(size_t x, size_t y, uint8_t* buffer_to_read, uint8_t* buffer_to_write) {

    size_t neigh_count = 0;
    for (size_t i = field_width_ - current_rule_->radius + x; i <= field_width_ + current_rule_->radius + x; ++i) {
        for (size_t j = field_height_ - current_rule_->radius + y; j <= field_height_ + current_rule_->radius + y; ++j) {
            if (i == field_width_ + x && j == y + field_height_) {
                continue;
            }
            if (GetPixel(i % field_width_, j % field_height_, buffer_to_read) == FULL_) {
                ++neigh_count;
            }
        }
    }

  uint8_t current_cell = GetPixel(x, y, buffer_to_read);
  SetPixel(x, y, current_cell, buffer_to_write);


  if (current_cell == EMPTY_) {
    if (current_rule_->is_arriving(neigh_count)) {
      SetPixel(x, y, FULL_, buffer_to_write);
      const auto this_color = (*current_pallete_)[FULL_];
      SetPixelColor(x, y, this_color.r, this_color.g, this_color.b);
    } else {
      SetPixel(x, y, EMPTY_, buffer_to_write);
      const auto this_color = (*current_pallete_)[EMPTY_];
      SetPixelColor(x, y, this_color.r, this_color.g, this_color.b);
    }
  } else if (current_cell == FULL_) {
    if (current_rule_->is_dying(neigh_count)) {
      SetPixel(x, y, EMPTY_, buffer_to_write);
    } else if (current_rule_->is_getting_older(neigh_count)) {
      unsigned char offset = (FULL_ - EMPTY_) / current_rule_->maximum_age;
      if (offset > current_cell) {
        current_cell = EMPTY_;
      } else {
        current_cell -= offset;
      }
      SetPixel(x, y, current_cell, buffer_to_write);
      const auto this_color = (*current_pallete_)[current_cell];
      SetPixelColor(x, y, this_color.r, this_color.g, this_color.b);
    } else {
      SetPixel(x, y, FULL_, buffer_to_write);
      const auto this_color = (*current_pallete_)[FULL_];
      SetPixelColor(x, y, this_color.r, this_color.g, this_color.b);
    }
  } else {
    unsigned char offset = (FULL_ - EMPTY_) / current_rule_->maximum_age;
    if (offset > current_cell) {
      current_cell = EMPTY_;
    } else {
      current_cell -= offset;
    }
    SetPixel(x, y, current_cell, buffer_to_write);
    const auto this_color = (*current_pallete_)[current_cell];
    SetPixelColor(x, y, this_color.r, this_color.g, this_color.b);
  }
}

Field& Field::GetInstance() {
    static Field obj;
    return obj;
}

void Field::SetGameRule(GameRule* rule) {
    current_rule_ = rule;
}

void Field::SetColorPallette(std::vector<GameColor>* pallette) {
    current_pallete_ = pallette;
}

void Field::SetFrameDelayMilliseconds(size_t val) {
  frame_milliseconds_delay_ = std::max<size_t>(5, std::min<size_t>(val, 4'000));

}

void Field::CreateUpdateThreads() {
  thread_creation_mutex.lock();
  thread_should_start = std::vector<std::atomic_bool>(threads_count);

  for (size_t t = 0; t < threads_count; ++t) {
    thread_should_start[t].store(false);
    computing_threads_.emplace_back(&Field::ThreadUpdateFunction, this, t, t);
    
  };
  thread_creation_mutex.unlock();
}

void Field::ThreadUpdateFunction(size_t thread_id, size_t start_x) {
  thread_creation_mutex.lock();
  thread_creation_mutex.unlock();

  while (processing_) {

    {
      std::unique_lock<std::mutex> lk(compute_start_mutex);
      compute_start_cv.wait(lk, [&](){ return thread_should_start[thread_id].load(std::memory_order_acq_rel); });
    }

    thread_should_start[thread_id].store(false, std::memory_order_acq_rel);
    
    auto buff_r = GetReadBuffer();
    auto buff_w = GetWriteBuffer();

    for (size_t x = start_x; x < field_height_; x += threads_count) {
      for (size_t y = 0; y < field_width_; ++y) {
        UpdatePixel(x, y, buff_r, buff_w);
      }
    }

    current_threads_finished.fetch_add(1, std::memory_order_acq_rel);
    if (current_threads_finished.load() == threads_count) {
      compute_end_cv.notify_one();
    }
  }
  
}

void Field::MultiThreadUpdating() {

  size_t frame_counter = 0;

  while (true) {
    std::this_thread::sleep_for(std::chrono::milliseconds(frame_milliseconds_delay_));
    
    {
      std::lock_guard<std::mutex> l(debug_m);
      std::cout << "Update start frame "  << ++frame_counter << std::endl;
    }

    // ranged for will not work
    for (size_t i = 0; i < threads_count; ++i) {
      thread_should_start[i].store(true, std::memory_order_acq_rel);
    }

    compute_start_cv.notify_all();

    std::unique_lock<std::mutex> lk(compute_end_mutex);
    compute_end_cv.wait(lk, [&](){ return current_threads_finished.load(std::memory_order_acquire) == threads_count; });

    SwitchBuffer();
  
    current_threads_finished.store(0, std::memory_order_release);
  }

  for (size_t i = 0; i < threads_count; ++i) {
    computing_threads_[i].join();
  }
  
}

void Field::SetPixelAt(int x, int y, uint8_t val) {
  size_t x_at = static_cast<size_t>((x + field_width_) % field_width_);
  size_t y_at = static_cast<size_t>((y + field_height_) % field_height_);
  SetPixel(x_at, y_at, val, GetReadBuffer());
}