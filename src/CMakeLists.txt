add_executable(main main.cpp)
target_link_libraries(main PUBLIC LLDEnzymeFlags)
install(TARGETS main DESTINATION bin)
