# ecoTemperatura

<img src="https://github.com/iotlibre/EcoPower/blob/master/docs/ecopower_equipo.png" align="right">
ecoTemperatura esta pensado para tomar las medidas de temperatura de una intalación con un gran número de sensores. Hasta 48 en un mismo dispositivo

El hardware utilizado como base es el hardware de ecoPower con un pequeño cambio de componentes para que se pueda adaptar a la lecturas de sondas del tipo DS18b20

En el un edificio podemos tener tantos dispositivos de la familia ecoPower como sean necesarios y el servidor los integrará en la misma instalación sin necesidad de configuraciones adicionales o cambios en el Firmware.

La comunicación se hace mediante Wifi por lo que no es necesario el cableado de datos al equipo solamente es preciso que esté dentro de la cobertura de la red WIFI del edificio.

Para su uso no son necesarios conocimientos de informática aunque todos los desarrollos y el hardware están hechos bajo licencias libres lo que permite la modificación y mejora de las funcionalidades.

## Listado con las principales características
Las principales características de EcoPower son:
- 6 entradas diferenciadas para sensores de temperatura con capacidad para 8 sensores cada una de ellas
- Media de temperatura desde -55°C a +125°C
- Precisión en las medida de energía: ± 0,5C desde -10°C a +85°C
- Comunicación a Internet por WIFI local 
- Configurable vía Web
- Estandard: IEEE 802.11 b/g/n
- Alimentación a 220 voltios de corriente alterna. Rango: 85 ~ 264VAC 
- Montaje en carril din
- La PCB integra un Arduino nano con el ESP8266 12E
- Compatible con el [servidor de Open Energy Monitor](https://emoncms.org/)

## Puesta a punto
La puesta a punto de EcoPower consta de dos partes:
- La configuración en la instalación
- El firmware de Arduino

### La configuración en la instalación
En este punto se definen los parámetros del servidor de destino y la wifi local a la que va a estar conectado el dispositivo. Con este fin, la primera vez que se ponga en servicio el ESP y siempre que no encuentre la WIFI configurada, el ESP 8266 12E creará su propio punto de acceso, su propia red WIFI . Conectandose a cualquier dirección a través de este punto de acceso nos aparecerá la página de configuración del ESP. Tengase en cuenta que una  vez configurado el ESP y conectado a una red WIFI el router le asignará una única dirección IP a la que será necesario acceder para cambiar la configuración.

En caso de que se quiera actualizar el firmware del ESP a la última versión, este se puede encontrar en: [EcoPower-emonESP ](https://github.com/iotlibre/20180328_EmonESP)

### El firmware de Arduino
El firmware que que esta cargado por defecto en el arduino nano funciona correctamente para tranformadores de intensidad de 100A/50mA sin embargo, si quiere cambiar la configuración puede encontrar la última actualización del firmware en este repositorio:[ecoTemperatura](https://github.com/iotlibre/ecoTemperatura)
