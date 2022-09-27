cmake_minimum_required( VERSION 3.5 )

project( gdal-test )

find_package( GDAL REQUIRED )
find_package( OpenCV REQUIRED )

add_library( gdal-test
    SHARED
    main.cpp
)

target_link_libraries( gdal-test
    PRIVATE
        GDAL::GDAL
        ${OpenCV_LIBS}
)

