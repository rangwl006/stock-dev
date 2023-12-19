add_executable(app main.cpp)
target_include_directories(app PUBLIC
                               ${CMAKE_SOURCE_DIR}/inc)
target_link_libraries(app PUBLIC api_utils request_builder data_updater cpr::cpr)
