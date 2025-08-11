#pragma once
#include "game_colors.h"
#include "game_rule.h"
#include "stdafx.h"


class Controller;

class Field {
 private:
  Field();
  ~Field();

  Controller* controller_;

  size_t field_width_ = 512;
  size_t field_height_ = 512;

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

  bool paused_ = false;

  std::atomic_bool should_reinitialize_ = false;
  size_t reinitialize_width_ = 0;
  size_t reinitialize_height_ = 0;

  size_t threads_count = 56;
  std::atomic<size_t> current_threads_finished;

  std::mutex thread_creation_mutex;
  std::vector<std::thread> computing_threads_;

  std::mutex compute_start_mutex;
  std::mutex compute_end_mutex;
  std::mutex debug_m;

  std::condition_variable compute_start_cv;
  std::condition_variable compute_end_cv;

  // average bool can be ovverding due to cache
  std::vector<std::atomic_bool> thread_should_start;

  size_t frame_milliseconds_delay_ = 0;

  float current_fps_ = 0;

  inline size_t BufferIndex(size_t x, size_t y);

  void ReinitializeBuffer();
  void ReinitializeColorBuffer();

  void SetPixel(size_t x, size_t y, uint8_t val, uint8_t* buffer);
  void SetPixelColor(size_t x, size_t y, uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);
  uint8_t GetPixel(size_t x, size_t y, uint8_t* buffer);
  void UpdatePixel(size_t x, size_t y, uint8_t* buffer_to_read, uint8_t* buffer_to_write);

  void ThreadUpdateFunction(size_t thread_id, size_t start_x);

 public:
  static Field& GetInstance();
  void SetController(Controller* controller);

  void CreateUpdateThreads();
  void MultiThreadUpdating();

  uint8_t* GetColorBuffer();

  void SetNewDimensions(size_t x, size_t y);

  void SetGameRule(GameRule* rule);
  GameRule* GetGameRule();

  void SetColorPallette(std::vector<GameColor>* pallette);

  void SetFrameDelayMilliseconds(size_t val);
  float GetFPS();
  void SetPause(float val);
  void StopThreads();

  void SetPixelAt(int x, int y, uint8_t val);
  // uint8_t GetPixelAt(int x, int y);
};