<h1 align="center"><b>H DEFENSE</b></h1>

## Logo:
![logo](/ProyectoH/resources/images/LogodeHDefense.png)
<h2 align="center"><b> NineandoCorp</b></h2>


## Enlaces:
[Web del juego](https://pokoli0.github.io/PVLI-Taxistas/)
[Presentaciones](/Presentaciones/)
[UML]()
[QA]()
[GDD](#1---GDD)

## GDD
---
### Índice

### 1. Ficha técnica
- **Título**: H Defense
- **Género**: Tower Defense
- **Target**: Público joven con interés en juegos de estrategia
- **Rating**: +7
- **Plataforma**: PC
- **Modos de juego**: Campaña / Infinito

### 2. Descripción
"H Defense” es un videojuego de estrategia del género tower defense que te sumerge en un mundo fantástico que es asediado por hordas de diversas criaturas fantásticas y hostiles. Tu misión es defender la última fortaleza del Planeta H utilizando una variedad de torres defensivas y estrategias de diferente tipo.

### 3. Estética
El juego cuenta con una estética *Pixelart* no muy pronunciada. 
Asimismo, se cuenta con un estilo de fantasía, por tanto, habrá ciertas zonas con elementos oscuros y otras con elementos más llamativos. 
Además, puesto que el elemento principal del juego es la magia, esta se representa con el color morado.

La perspectiva del juego es isométrica. Sin embargo, algunos de los assets, principalmente enemigos y torres están en 2D, por tanto, se puede considerar un juego 2.5D. 

#### 3.1 Estética del escenario
El escenario está ambientado en un prado mágico  entre montañas. Así, el escenario cuenta con zonas donde predomina el color verde (prado) y zonas donde predomina el color gris (montaña). 

#### 3.2 Estética de enemigos
En los enemigos, en contraste al escenario, destacan colores más oscuros, con un aspecto más tenebroso.

#### 3.3 Estética de torres
Puesto que el juego está ambientado en  un mundo de fantasía, las torres cuentan con ciertos artefactos mágicos, y, por lo tanto, cada cual tiene los colores de los elementos que empleen. Por ejemplo, la torre Llama de Fénix cuenta, en su mayoría, con elementos de tono rojizo y naranja. 
Por otra parte, el resto de torres que no cuentan con un elemento en específico  contarán con diversos elementos con aspecto morado, puesto que es el color principal que representa a la magia.

#### 3.4 Estética de UI y menús
Al  igual que las torres, la estética de las distintas interfaces cuentan con el morado como color principal. 
No obstante, en contraste con la estética del escenario, estas interfaces van a tender a tonos más oscuros, puesto que así será más sencillo para el jugador reconocerlas durante la partida. 

### 4. Jugabilidad
En este apartado definiremos las mecánicas del juego, las cuales podemos dividir en 5 apartados principales: cámara, las mecánicas únicas del jugador y las mecánicas del escenario, enemigos y torres. Con todo esto englobamos las propiedades que harán jugable nuestro juego. 

#### 4.1 Cámara
La cámara se colocará en la parte superior de la pantalla y mostrará todos los puntos de spawn.
Asimismo, la cámara se puede desplazar en el eje x e y para explorar el mapa.

![Isometría](ProyectoH/resources/images/jugabilidad_camara.png)

#### 4.2. Mecánicas del jugador
El jugador será capaz de realizar diferentes acciones, desde interactuar con el mapa hasta gestionar toda la partida (pausar, acelerar…). Dichas acciones se podrán manejar con el ratón, excepto algunas que tendrán atajos de teclado. A continuación, se explican más detalladamente:

#### 4.2.1 Interacción con el mapa
- Manteniendo el click izquierdo sobre el icono de la torre deseada en la barra inferior, arrastrar hasta la posición en la que se quiere colocar. Dicha torre no se puede mover una vez haya sido colocada.
- Las torres se podrán quitar sin recuperar ni perder dinero o cambiar de posición a cambio de dinero.
- Haciendo click sobre las torres colocadas, aparecerá un pop-up con información de la torre y tendremos la opción de mejorarla.
- Si has arrastrado una torreta y no la has colocado puedes cancelar la selección con click derecho.

#### 4.2.2 Gestión de la partida
- Pause: se podrá hacer click en un botón (parte superior derecha de la pantalla) o pulsar la tecla “ESCAPE” para pausar la partida. 
- Multiplicador de velocidad: se podrá hacer click en un botón en la parte superior derecha de la pantalla (>>) o pulsar la tecla “SPACE” para reproducir más rápido el transcurso de la partida (X2), si volvemos a darle al botón o presionar la tecla, la velocidad del transcurso del tiempo volverá a la normalidad (X1).
- Empezar: para empezar la ronda se podrá hacer click en dicho botón (parte inferior derecha de la pantalla) o pulsar la tecla “ENTER”.

#### 4.3 Mécanicas del escenario

El escenario está diseñado en 2D pero dando una sensación tridimensional con vista isométrica.

#### 4.3.1 Caminos
Para entender mejor el diseño del escenario es necesario diferenciar entre puntos de spawneo (lugares donde aparecen los enemigos) y destinos de los caminos. 

Los puntos de spawneo se encuentran en los límites del mapa. De cada spawn puede salir un grupo de enemigos con una ruta preestablecida de la cual saldrá por pantalla una sola vez justo antes de salir el primer enemigo. Los enemigos aparecerán de 1 en 1 hasta no haber más y con un intervalo que puede ser irregular. Esto da como resultado una sensación de progresión en la dificultad durante las rondas.

Asimismo, los caminos de cada grupo pueden cruzarse o ir por el mismo lado ya que los enemigos no se estorban entre ellos.

La evolución del escenario va en base a esta tabla: 

| NIVEL  | SPAWNS | DESTINOS |
|:---:|:---:|:---:|
| 1| 1 | 1 |
| 2| 2 | 2 |
| 3| 3 | 2 |
| 4| 5 | 2 |

#### 4.3.2 Zonas del escenario
Una de las mecánicas más características del escenario son las zonas del mismo, 	puesto que estas limitan el tipo de torre que se pueden situar sobre ellas.

Estas zonas son: 

| ZONAS | |
| :---: | :---:|
| Pradera | Suelen ser las zonas más próximas a los caminos. En ella solo se pueden situar torres de poco alcance o que necesiten situarse al lado del camino.|
|Montaña| Son zonas más alejadas de los caminos. En ella solo se pueden poner torres de gran alcance o torres que ataque a enemigos aéreos|
|Lagos|Estas zonas imposibilitan poner todo tipo de torres.|