<div align="center" id="top"> 
  <img src="./.github/app.gif" alt="MQTT_Thingsboard" />

  &#xa0;

  <!-- <a href="https://mqtt_thingsboard.netlify.app">Demo</a> -->
</div>

<h1 align="center">MQTT_Thingsboard</h1>

<p align="center">
  <img alt="Github top language" src="https://img.shields.io/github/languages/top/Franklingo13/mqtt_thingsboard?color=56BEB8">

  <img alt="Github language count" src="https://img.shields.io/github/languages/count/Franklingo13/mqtt_thingsboard?color=56BEB8">

  <img alt="Repository size" src="https://img.shields.io/github/repo-size/Franklingo13/mqtt_thingsboard?color=56BEB8">

  <img alt="License" src="https://img.shields.io/github/license/Franklingo13/mqtt_thingsboard?color=56BEB8">

  <!-- <img alt="Github issues" src="https://img.shields.io/github/issues/Franklingo13/mqtt_thingsboard?color=56BEB8" /> -->

  <!-- <img alt="Github forks" src="https://img.shields.io/github/forks/Franklingo13/mqtt_thingsboard?color=56BEB8" /> -->

  <!-- <img alt="Github stars" src="https://img.shields.io/github/stars/Franklingo13/mqtt_thingsboard?color=56BEB8" /> -->
</p>

<!-- Status -->

<!-- <h4 align="center"> 
	🚧  MQTT_Thingsboard 🚀 Under construction...  🚧
</h4> 

<hr> -->

<p align="center">
  <a href="#dart-about">About</a> &#xa0; | &#xa0; 
  <a href="#sparkles-features">Features</a> &#xa0; | &#xa0;
  <a href="#rocket-technologies">Technologies</a> &#xa0; | &#xa0;
  <a href="#white_check_mark-requirements">Requirements</a> &#xa0; | &#xa0;
  <a href="#checkered_flag-starting">Starting</a> &#xa0; | &#xa0;
  <a href="#memo-license">License</a> &#xa0; | &#xa0;
  <a href="https://github.com/Franklingo13" target="_blank">Author</a>
</p>

<br>

## :dart: Acerca del Proyecto ##

Este repositorio alberga el código fuente para un sistema de monitoreo basado en nodos sensores interconectados mediante el protocolo ESP-NOW. La comunicación entre los nodos sensores y el nodo gateway se realiza de manera eficiente y de baja potencia gracias a ESP-NOW. El nodo gateway, a su vez, utiliza MQTT para enviar los datos recolectados a la plataforma Thingsboard para su visualización y análisis.

### Estructura de Tramas ###

El proyecto utiliza diferentes tramas según el tipo de sensor, mejorando así la eficiencia de la comunicación. A continuación se describen las estructuras de las tramas:

Tipo 1 (DHT11):
 2 bits    8 bits    9 bits       7 bits
+------+---------+---------+---------+
| tipo |   id    |temperat.| humedad |
+------+---------+---------+---------+

Tipo 2 (ADC):
 2 bits    8 bits    8 bits
+------+---------+---------+
| tipo |   id    |   adc   |
+------+---------+---------+

Tipo 3 (Botón):
 2 bits    8 bits    1 bit
+------+---------+---------+
| tipo |   id    | button  |
+------+---------+---------+


## :sparkles: Features ##

:heavy_check_mark: Feature 1;\
:heavy_check_mark: Feature 2;\
:heavy_check_mark: Feature 3;

## :rocket: Tecnologías Utilizadas ##

El proyecto hace uso de las siguientes tecnologías:

- [ESP-NOW](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/network/esp_now.html)
- [MQTT](https://mqtt.org/)
- [Thingsboard](https://thingsboard.io/)

## :white_check_mark: Requirements ##

Before starting :checkered_flag:, you need to have [Git](https://git-scm.com) and [Node](https://nodejs.org/en/) installed.

## :checkered_flag: Inicio Rápido ##

```bash
# Clone this project
$ git clone https://github.com/Franklingo13/mqtt_thingsboard

# Access
$ cd mqtt_thingsboard

# Install dependencies
$ yarn

# Run the project
$ yarn start

# The server will initialize in the <http://localhost:3000>
```

## :memo: License ##

Este proyecto está bajo la Licencia MIT. Para más detalles, consulta el archivo [LICENSE](LICENSE).


Made with :heart: by <a href="https://github.com/Franklingo13" target="_blank">Franklin</a>

&#xa0;

<a href="#top">Back to top</a>
