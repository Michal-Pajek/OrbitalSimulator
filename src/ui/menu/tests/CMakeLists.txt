target_sources(orbital_tests PRIVATE
    MenuTests.cpp
)

target_link_libraries(orbital_tests PRIVATE
    ui_menu
)
