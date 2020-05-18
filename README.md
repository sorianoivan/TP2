Nombre: Ivan Soriano

Padrón: 102342

URL: https://github.com/sorianoivan/TP2.git



# Trabajo Práctico 2

## <u>Clases</u>

A continuación, se presenta un diagrama con las clases mas importantes del trabajo práctico:

![Clases](/img/Clases.png)

Aclaración: No agrego la clase *TP* ya que esta funciona como el hilo principal del programa y no aportaría mas claridad al diagrama.

### <u>Cola Bloqueante</u>

La clase *ColaBloqueante* consiste de 4 elementos: una variable que indica si fue cerrada(esto ocurre cuando se termina de leer el archivo del mapa), un *mutex(std::mutex)*, una *condition variable(std::condition_variable)* y una *cola(std::queue)*.  Cada cola es cargada a medida que se lee el archivo del mapa. Para permitir que distintos threads recolectores puedan acceder a su respectiva cola bloqueante y sacar recursos sin race conditions o deadlocks se usa tanto la variable booleana *cerrada* y el método *empty()* de la cola. Primero, cuando un recolector quiera quitar un recurso, se fijara que la cola bloqueante no este cerrada y vacía. Si esta tanto cerrada como vacía el recolector no puede hacer nada así que termina de trabajar. En caso contrario, procederá a quitar el recurso de la cola. Como puede suceder que antes de que el recolector tome el mutex de la cola otros hayan quitado recursos o esta se haya cerrado, el recolector volverá a preguntar si esta vacía. Si ademas de estar vacía esta cerrada, el recolector tomará un *NoRecurso* y terminara de trabajar. En caso de que no este cerrada, esperara a que la condition variable le notifique que agregaron un recurso a la cola, entonces lo quitara de la cola, esperara 50ms y lo depositara en el inventario general. A continuación se presenta un diagrama de secuencia del trabajo de un recolector:

![Recolector](/img/Recolector.png)

### <u>Inventario</u>

El funcionamiento del Inventario es parecido al de la cola bloqueante. También posee una variable booleana que indica si esta cerrado(esto ocurre cuando todos los recolectores terminan de trabajar), un *mutex* y una *condition variable*. Cada vez que un recolector deposite un recurso en el inventario, este se fijara si hay recursos suficientes para alguna "receta" de los productores. Si esto ocurre la condition variable avisa a todos los productores que hay recursos disponibles para una receta, pero no especifica cual. Por su parte, cada vez que un productor quiera tomar un recurso del inventario se fijara que haya recursos suficientes para su receta o que el inventario no este cerrado. Si el inventario esta cerrado y no hay recursos suficientes el productor termina de trabajar, caso contrario procede a consumir los recursos del inventario y recibir los puntos de beneficio correspondientes. Luego, por la misma razón que los recolectores con sus colas bloqueantes, el productor preguntara devuelta si hay recursos suficientes para su receta. Si no los hay y ademas el inventario se cerro, el productor recibe 0 puntos de beneficio y termina de trabajar. Si el inventario no fue cerrado el productor esperara a que la condition variable avise que hay recursos disponibles, entonces el productor se fijara si hay recursos disponibles para su receta. Si no los hay seguirá esperando, pero si los hay consumirá los recursos y recibirá los puntos de beneficio correspondientes. Luego esperara 60ms y depositara los puntos en el monitor de puntos de beneficio apenas pueda. A continuación se presenta un diagrama de secuencia del trabajo de un recolector:

![Productor](/img/Productor.png)

### <u>Puntos de Beneficio</u>

Los puntos de beneficio simplemente están implementados como un Monitor, es decir, una variable que representa los puntos junto con un mutex para evitar race conditions.

