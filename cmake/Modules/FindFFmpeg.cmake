# FindFFmpeg.cmake
# Locate FFmpeg libraries and binaries

find_program(FFMPEG_EXECUTABLE NAMES ffmpeg)
find_program(FFPROBE_EXECUTABLE NAMES ffprobe)

find_library(AVCODEC_LIB avcodec)
find_library(AVFORMAT_LIB avformat)
find_library(AVUTIL_LIB avutil)

if (FFMPEG_EXECUTABLE AND FFPROBE_EXECUTABLE AND AVCODEC_LIB AND AVFORMAT_LIB AND AVUTIL_LIB)
  set(FFMPEG_FOUND TRUE)
endif()

if (FFMPEG_FOUND)
  message(STATUS "Found FFmpeg: ${FFMPEG_EXECUTABLE}")
  message(STATUS "Found FFprobe: ${FFPROBE_EXECUTABLE}")
else()
  message(FATAL_ERROR "FFmpeg or FFprobe not found.")
endif()

# Export variables for use in the project
set(FFMPEG_LIBRARIES ${AVCODEC_LIB} ${AVFORMAT_LIB} ${AVUTIL_LIB})
