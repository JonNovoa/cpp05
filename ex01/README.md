¿En qué consiste el ejercicio?

En el ex00 creamos un Bureaucrat.

Un Bureaucrat tenía:

Nombre
Grado

Por ejemplo:

Bob → grado 42

Y aprendimos que:

1   = grado MUY alto
42  = grado medio
100 = grado bajo
150 = grado MUY bajo

Ahora en ex01 vamos a darle un trabajo al Bureaucrat:

Firmar formularios.

Para eso creamos una nueva clase llamada Form.

¿Qué es un Form?

Un formulario tendrá:

Nombre
¿Está firmado?
Grado necesario para firmarlo
Grado necesario para ejecutarlo

Por ejemplo, imaginemos:

Form: "Contrato"

Ese formulario podría necesitar:

Grado 50 para firmarlo
Grado 30 para ejecutarlo

Y aquí está la parte importante.

¿Qué significa 50 y 30?

Cuando hacemos:

Form form("Contrato", 50, 30);

los parámetros son:

"Contrato" → nombre del formulario

50 → grado necesario para FIRMARLO

30 → grado necesario para EJECUTARLO

Es decir:

                    CONTRATO
                       │
             ┌─────────┴─────────┐
             │                   │
       Para firmarlo       Para ejecutarlo
          grado 50             grado 30
¿Qué significa "grado necesario"?

Recuerda que en este ejercicio:

1 es mejor que 50, y 50 es mejor que 100.

Por tanto, si un formulario necesita grado 50 para firmarlo:

Bureaucrat grado 30
30
↓
es mejor que 50

✅ Puede firmarlo.

Bureaucrat grado 50
50
↓
exactamente el necesario

✅ Puede firmarlo.

Bureaucrat grado 70
70
↓
es peor que 50

❌ No puede firmarlo.

Por eso la condición será:

bureaucrat.getGrade() <= 50
¿Y _gradeToSign?

Cuando decimos:

_gradeToSign

simplemente estamos guardando:

El grado máximo permitido para poder firmar ese formulario.

Por ejemplo:

_gradeToSign = 50

significa:

"Para firmarme necesitas tener grado 50 o mejor."

Por tanto:

1   → puede
20  → puede
49  → puede
50  → puede
51  → NO puede
100 → NO puede
150 → NO puede
¿Y _gradeToExecute?

Exactamente lo mismo, pero para ejecutar el formulario.

Si:

_gradeToExecute = 30

significa:

"Para ejecutar este formulario necesitas tener grado 30 o mejor."

Por ejemplo:

Bureaucrat grado 10 → puede ejecutar
Bureaucrat grado 25 → puede ejecutar
Bureaucrat grado 30 → puede ejecutar
Bureaucrat grado 31 → NO puede ejecutar
Bureaucrat grado 80 → NO puede ejecutar
Entonces, ¿por qué hay dos grados?

Porque firmar y ejecutar son cosas diferentes.

Por ejemplo:

Form form("Contrato", 50, 30);

significa:

Contrato

Para FIRMAR:
→ necesitas grado 50 o mejor

Para EJECUTAR:
→ necesitas grado 30 o mejor

Así puede ocurrir:

Bob → grado 40

Bob:

¿Puede firmarlo?
40 <= 50 → SÍ ✅

¿Puede ejecutarlo?
40 <= 30 → NO ❌

Es decir, Bob puede firmarlo pero no ejecutarlo.

Otro:

Alice → grado 20

Alice:

¿Puede firmarlo?
20 <= 50 → SÍ ✅

¿Puede ejecutarlo?
20 <= 30 → SÍ ✅
¿Qué pasa cuando creamos el Form?

Al crearlo:

Form form("Contrato", 50, 30);

tenemos:

Nombre:             Contrato
Firmado:            false
Grado para firmar:  50
Grado para ejecutar:30

El formulario empieza siempre sin firmar.

_signed = false

Luego un Bureaucrat puede intentar firmarlo.

¿Qué hace beSigned()?

Tenemos:

form.beSigned(bob);

Esto significa:

"Haz que este formulario sea firmado por Bob."

El formulario mira el grado de Bob.

Si puede firmarlo:

_signed = true

Si no puede:

throw Form::GradeTooLowException
¿Y qué añade signForm()?

En ex00 teníamos:

Bureaucrat bob("Bob", 40);

Ahora podremos hacer:

bob.signForm(form);

Y Bob intentará firmar el formulario.

Si puede:

Bob signed Contrato

Si no puede:

Bob couldn't sign Contrato because ...
En resumen, la película completa es esta

Tenemos:

                 BUREAUCRAT
                     │
                tiene un grado
                     │
                     ▼
                   FORM
                     │
          ┌──────────┴──────────┐
          │                     │
     grado para firmar     grado para ejecutar
          │
          ▼
   ¿Bureaucrat tiene
    grado suficiente?
       /          \
     SÍ            NO
     │              │
     ▼              ▼
 firmado        excepción

Y eso es todo el ejercicio.

Lo que cambia respecto a ex00:

Ex00:

Crear Bureaucrat, controlar sus grados y lanzar excepciones.

Ex01:

Crear Form, controlar los grados que necesita y permitir que un Bureaucrat intente firmarlo.

Y una cosa importante: en este ejercicio todavía no vamos a implementar que el Bureaucrat ejecute el formulario. El gradeToExecute simplemente forma parte de los datos del Form porque el enunciado lo pide; se utilizará más adelante en los siguientes ejercicios.

/*En una sola frase

Crear una clase Form que tenga un nombre, un estado de firmado
 y dos grados necesarios (uno para firmarlo y otro para ejecutarlo), 
 y hacer que los Bureaucrat puedan intentar firmarlo respetando las 
 reglas de grados y excepciones.
*/