#pragma once
#include "stdafx.h"
#include "game_rule.h"
#include "game_colors.h"

class Field {
    private:
    Field();
    ~Field();

    size_t field_width_ = 20;
    size_t field_height_ = 20;
    
    uint8_t read_buffer_ = 0;
    uint8_t* buffer_0_;
    uint8_t* buffer_1_;
    uint8_t* color_buffer_;

    uint8_t* GetReadBuffer();
    uint8_t* GetWriteBuffer();
    void SwitchBuffer();

    const uint8_t ACTIVE_ = 0;
    const uint8_t EMPTY_ = 0;
    const uint8_t FULL_ = 255;


    GameRule* current_rule_ = nullptr;
    std::vector<GameColor>* current_pallete_ = nullptr;

    bool processing_ = true;
    size_t threads_count = 2;
    std::atomic<size_t> current_threads_finished;

    std::mutex thread_creation_mutex;
    std::vector<std::thread> computing_threads_;

    std::mutex compute_start_mutex;
    std::mutex compute_end_mutex;
    std::mutex debug_m;

    std::condition_variable compute_start_cv;
    std::condition_variable compute_end_cv;
    //std::atomic_bool should_start = false;

    //average bool can be ovverding due to cache
    std::vector<std::atomic_bool> thread_should_start;

    size_t frame_milliseconds_delay_ = 100;

    inline size_t BufferIndex(size_t x, size_t y);

    void ReinitializeBuffer();
    void ReinitializeColorBuffer();

    void SetPixel(size_t x, size_t y, uint8_t val, uint8_t* buffer);
    void SetPixelColor(size_t x, size_t y, uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);

    uint8_t GetPixel(size_t x, size_t y, uint8_t* buffer);

    void UpdatePixel(size_t x, size_t y, uint8_t* buffer_to_read, uint8_t* buffer_to_write);

    
    void ThreadUpdateFunction(size_t thread_id, size_t start_x);

    

    public:

    void CreateUpdateThreads();

    void MultiThreadUpdating();

    static Field& GetInstance();
    void UpdateField() {
        for (size_t x = 0; x < field_width_; ++x) {
            for (size_t y = 0; y < field_height_; ++y) {
                UpdatePixel(x, y, GetReadBuffer(), GetWriteBuffer());
            }
        }
        read_buffer_ = (read_buffer_ == 0 ? 1 : 0);
    }

    void SetPixels() {
        for (size_t x = 3; x < 6; ++x) {
            for (size_t y = 2; y < 10; ++y) {
                SetPixel(x, y, FULL_, GetReadBuffer());
            }
        }
    }
    
    void SetGameRule(GameRule* rule);

    void SetColorPallette(std::vector<GameColor>* pallette);
    
    void SetFrameDelayMilliseconds(size_t val);

    void SetPixelAt(int x, int y, uint8_t val);

    uint8_t GetPixelAt(int x, int y);

    void show_current_count() {
        while(true) {
            std::this_thread::sleep_for(std::chrono::milliseconds(600));
            {
            std::lock_guard<std::mutex> l(debug_m);
            std::cout << "CTF" << current_threads_finished << std::endl;
            }
        }
    }

    uint8_t* GetColorBuffer();
};