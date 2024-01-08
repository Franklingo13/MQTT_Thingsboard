# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "D:/ESP32-IDF/esp-idf/components/bootloader/subproject"
  "D:/Documentos/WSN/PracticasWSN/MQTT_test/nuevo_mqtt/esp-idf-espnow-gateway/build/bootloader"
  "D:/Documentos/WSN/PracticasWSN/MQTT_test/nuevo_mqtt/esp-idf-espnow-gateway/build/bootloader-prefix"
  "D:/Documentos/WSN/PracticasWSN/MQTT_test/nuevo_mqtt/esp-idf-espnow-gateway/build/bootloader-prefix/tmp"
  "D:/Documentos/WSN/PracticasWSN/MQTT_test/nuevo_mqtt/esp-idf-espnow-gateway/build/bootloader-prefix/src/bootloader-stamp"
  "D:/Documentos/WSN/PracticasWSN/MQTT_test/nuevo_mqtt/esp-idf-espnow-gateway/build/bootloader-prefix/src"
  "D:/Documentos/WSN/PracticasWSN/MQTT_test/nuevo_mqtt/esp-idf-espnow-gateway/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/Documentos/WSN/PracticasWSN/MQTT_test/nuevo_mqtt/esp-idf-espnow-gateway/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "D:/Documentos/WSN/PracticasWSN/MQTT_test/nuevo_mqtt/esp-idf-espnow-gateway/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
