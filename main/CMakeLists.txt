# This file was automatically generated for projects
# without default 'CMakeLists.txt' file.q


idf_component_register(
    SRC_DIRS
        "." 
        "classes" 
        "classes/physical_interface"  
    INCLUDE_DIRS "./"
    REQUIRES "TM1637" "StepperDriver" "TimeAlarms" "Time" "arduino" "ArduinoJson" "nvs_flash"
)

