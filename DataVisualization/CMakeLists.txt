# Build all eleven production modules into one reusable library.
# Labels and Statistics use inline/template header definitions; their source
# files include those headers. No library source contains an application main().
add_library(dataviz
    src/Plot.cpp
    src/AxisScale.cpp
    src/Renderer.cpp
    src/ScatterPlot.cpp
    src/BarPlot.cpp
    src/LinePlot.cpp
    src/DataLoader.cpp
    src/DataPreprocessor.cpp
    src/Statistics.cpp
    src/Labels.cpp
    src/ImageExporter.cpp
)
# PUBLIC propagates the include directory to every program linking dataviz.
target_include_directories(dataviz PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_options(dataviz PRIVATE -Wall -Wextra -Wpedantic)

# Keep all thirteen existing tests and their original names/assertions.
foreach(name
    bar data_loading image_export lineplot renderer scaling scatter
    integration statistics preprocessing labels line plot_behavior
)
    add_executable(test_${name} tests/test_${name}.cpp)
    target_link_libraries(test_${name} PRIVATE dataviz)
    # Assertions must stay active even if a configuration defines NDEBUG.
    target_compile_options(test_${name} PRIVATE -UNDEBUG)
    # Each test owns its fixture/output directory and needs no command arguments.
    file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${name}/data)
    add_test(NAME ${name} COMMAND test_${name})
    set_tests_properties(${name} PROPERTIES
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${name}
    )
endforeach()

# The integrated example reads a CSV and writes three SVGs to an existing folder.
add_executable(csv_demo examples/main.cpp)
target_link_libraries(csv_demo PRIVATE dataviz)

# These examples demonstrate the public library interfaces.
add_executable(example_inheritance examples/example_inheritance.cpp)
add_executable(example_polymorphism examples/example_applying_Polymorphism.cpp)
add_executable(example_bar examples/example_barplot.cpp)
add_executable(example_line examples/example_lineplot.cpp)
foreach(name inheritance polymorphism bar line)
    target_link_libraries(example_${name} PRIVATE dataviz)
endforeach()

# Every historical teaching program owns a main(), so each is a separate
# executable. These programs do not supply production library implementations.
# Preserve the existing target names when relocating their source files.
add_executable(legacy_statistics examples/legacy_statistics.cpp)
add_executable(legacy_AxisScale examples/teaching/axis_scale_inheritance.cpp)
add_executable(legacy_DataPreprocessor examples/teaching/data_preprocessor_inheritance.cpp)
add_executable(legacy_Labels examples/teaching/labels_include_demo.cpp)
add_executable(teaching_template examples/teaching/label_class_template.cpp)
add_executable(teaching_templates examples/teaching/statistics_templates.cpp)
add_executable(teaching_templatestruct examples/teaching/label_struct_template.cpp)

# These two teaching entry points previously lived in production source paths.
# Keep both old Labels copies as distinct files to preserve their provenance.
add_executable(teaching_labels examples/teaching/labels_src_demo.cpp)
add_executable(teaching_statistics examples/teaching/statistics_array_templates.cpp)
