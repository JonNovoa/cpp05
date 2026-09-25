# CPP05 — Repetition and Exceptions

## 1. Objetivo del módulo

CPP05 está centrado principalmente en:

* Excepciones.
* `try / catch / throw`.
* Herencia.
* Polimorfismo.
* Clases abstractas.
* Orthodox Canonical Form.
* Referencias y punteros.
* Gestión de memoria.
* Punteros a funciones.

El módulo empieza con una clase sencilla (`Bureaucrat`) y va construyendo progresivamente un sistema de formularios.

La evolución es:

```text
ex00
Bureaucrat
   ↓
ex01
Bureaucrat + Form
   ↓
ex02
Bureaucrat + AForm + formularios concretos
   ↓
ex03
Intern + creación automática de formularios
```

---

# 2. Excepciones

Una excepción sirve para indicar que ha ocurrido un error o una situación que no podemos resolver normalmente.

En C++ utilizamos:

```cpp
throw
```

para lanzar una excepción.

```cpp
throw GradeTooLowException();
```

Y:

```cpp
try
{
	// CÓDIGO QUE PUEDE FALLAR
}
catch (std::exception &e)
{
	// TRATAMOS EL ERROR
	std::cout << e.what() << std::endl;
}
```

### Flujo

```text
try
  ↓
se produce un error
  ↓
throw
  ↓
catch
  ↓
e.what()
```

---

# 3. `std::exception`

Nuestras excepciones heredan de:

```cpp
std::exception
```

Por ejemplo:

```cpp
class GradeTooHighException : public std::exception
{
	public:
		const char *what() const throw();
};
```

Y después:

```cpp
const char *Bureaucrat::GradeTooHighException::what() const throw()
{
	return ("Grade is too high!");
}
```

Esto nos permite hacer:

```cpp
catch (std::exception &e)
```

y obtener el mensaje mediante:

```cpp
e.what()
```

---

# 4. Ex00 — Bureaucrat

En ex00 creamos la clase:

```text
Bureaucrat
```

Cada `Bureaucrat` tiene:

```cpp
const std::string _name;
int _grade;
```

El grado va de:

```text
1   → mejor grado
150 → peor grado
```

Por tanto:

```text
1
2
3
...
149
150
```

Cuanto menor sea el número, mayor es el rango.

---

## 4.1. Excepciones de Bureaucrat

Tenemos:

```cpp
GradeTooHighException
GradeTooLowException
```

Si intentamos crear:

```cpp
Bureaucrat("Bob", 0);
```

el grado es demasiado alto.

Si hacemos:

```cpp
Bureaucrat("Bob", 151);
```

el grado es demasiado bajo.

---

## 4.2. Incrementar y decrementar

Tenemos:

```cpp
incrementGrade()
decrementGrade()
```

`incrementGrade()` significa mejorar el grado:

```text
50 → 49
```

`decrementGrade()` significa empeorarlo:

```text
50 → 51
```

No podemos pasar de:

```text
1
```

hacia arriba ni de:

```text
150
```

hacia abajo.

---

# 5. Orthodox Canonical Form

A partir de los ejercicios donde se pide, nuestras clases utilizan:

```cpp
Class();
Class(const Class &other);
Class &operator=(const Class &other);
~Class();
```

Son:

1. Constructor por defecto.
2. Constructor de copia.
3. Operador de asignación.
4. Destructor.

---

## 5.1. Constructor de copia

Se utiliza cuando estamos creando un objeto nuevo a partir de otro:

```cpp
Bureaucrat a("Bob", 50);

Bureaucrat b(a);
```

Aquí `b` es un objeto nuevo.

---

## 5.2. Operador de asignación

Se utiliza cuando los dos objetos ya existen:

```cpp
Bureaucrat a("Bob", 50);
Bureaucrat b("John", 100);

b = a;
```

No se crea `b`.

`b` ya existía y ahora copiamos sus datos.

---

# 6. Ex01 — Form

En ex01 añadimos:

```text
Form
```

Un formulario tiene:

```cpp
const std::string _name;
bool _signed;
const int _gradeToSign;
const int _gradeToExecute;
```

---

## 6.1. Firmar un formulario

El método:

```cpp
beSigned()
```

comprueba si el `Bureaucrat` tiene suficiente grado.

Por ejemplo:

```text
Form necesita grado 50
Bureaucrat tiene grado 40
```

Puede firmar porque:

```text
40 < 50
```

Pero:

```text
Form necesita grado 50
Bureaucrat tiene grado 60
```

No puede firmar porque:

```text
60 > 50
```

---

# 7. Relación entre Bureaucrat y Form

En ex01 añadimos:

```cpp
void signForm(AForm &form);
```

El `Bureaucrat` intenta firmar el formulario.

El propio `Form` decide si puede firmarse:

```text
Bureaucrat
    │
    │ signForm()
    ↓
  Form
    │
    │ beSigned()
    ↓
¿Tiene grado suficiente?
    │
 ┌──┴──┐
Sí     No
│       │
firma   throw
```

---

# 8. Ex02 — AForm

En ex02 `Form` pasa a llamarse:

```text
AForm
```

La `A` significa que es una clase **abstracta**.

La hacemos abstracta mediante:

```cpp
virtual void execute(Bureaucrat const &executor) const = 0;
```

El `= 0` significa que la función es puramente virtual.

Por tanto no podemos crear directamente:

```cpp
AForm form;
```

Pero sí:

```cpp
RobotomyRequestForm form("Bender");
```

---

# 9. Formularios concretos

En ex02 creamos tres formularios.

```text
                 AForm
                /  |  \
               /   |   \
      Shrubbery  Robotomy  Presidential
```

---

## 9.1. ShrubberyCreationForm

Necesita:

```text
Grado para firmar: 145
Grado para ejecutar: 137
```

Al ejecutarse crea:

```text
<target>_shrubbery
```

Por ejemplo:

```text
home_shrubbery
```

y escribe árboles ASCII.

---

## 9.2. RobotomyRequestForm

Necesita:

```text
Grado para firmar: 72
Grado para ejecutar: 45
```

Al ejecutarse:

1. Hace ruido de perforación.
2. Tiene aproximadamente un 50% de posibilidades de éxito.
3. Informa del resultado.

```text
* drilling noises *
```

---

## 9.3. PresidentialPardonForm

Necesita:

```text
Grado para firmar: 25
Grado para ejecutar: 5
```

Al ejecutarse informa de que el objetivo ha sido perdonado por:

```text
Zaphod Beeblebrox
```

---

# 10. Polimorfismo

Una de las ideas importantes de ex02 es que podemos trabajar con:

```cpp
AForm *
```

aunque el objeto real sea:

```cpp
RobotomyRequestForm
```

Por ejemplo:

```cpp
AForm *form = new RobotomyRequestForm("Bender");
```

El tipo del puntero es:

```text
AForm *
```

pero el objeto real es:

```text
RobotomyRequestForm
```

Gracias al método virtual:

```cpp
virtual void execute(...) const = 0;
```

se ejecuta el `execute()` correspondiente al formulario real.

---

# 11. `executeForm()`

En ex02 añadimos a `Bureaucrat`:

```cpp
void executeForm(AForm const &form);
```

El funcionamiento es parecido a `signForm()`:

```text
Bureaucrat
    │
    │ executeForm()
    ↓
  AForm
    │
    │ execute()
    ↓
¿Puede ejecutarlo?
    │
 ┌──┴──┐
Sí     No
│       │
acción  throw
```

El formulario comprueba:

1. Que esté firmado.
2. Que el `Bureaucrat` tenga suficiente grado.

---

# 12. Ex03 — Intern

En ex03 aparece:

```text
Intern
```

El `Intern` no tiene:

* nombre
* grado
* características propias

Su función principal es:

```cpp
AForm *makeForm(const std::string &formName,
				const std::string &target);
```

---

# 13. ¿Qué hace `makeForm()`?

Recibe:

```text
nombre del formulario
        +
target
```

Por ejemplo:

```cpp
intern.makeForm("robotomy request", "Bender");
```

El `Intern` reconoce el nombre y crea:

```cpp
RobotomyRequestForm("Bender");
```

pero devuelve:

```cpp
AForm *
```

---

# 14. Punteros a funciones

La parte más nueva de ex03 es utilizar un array de funciones para evitar un enorme:

```cpp
if
else if
else if
```

Tenemos:

```cpp
AForm *createShrubbery(const std::string &target);
AForm *createRobotomy(const std::string &target);
AForm *createPardon(const std::string &target);
```

Cada función crea un formulario diferente.

Después tenemos:

```cpp
AForm *(*create[3])(const std::string &)
```

Esto significa:

> Un array de 3 punteros a funciones que reciben un `std::string` y devuelven un `AForm *`.

---

# 15. Tabla utilizada por Intern

Tenemos:

```cpp
std::string names[3] =
{
	"shrubbery creation",
	"robotomy request",
	"presidential pardon"
};
```

Y:

```cpp
AForm *(*create[3])(const std::string &) =
{
	createShrubbery,
	createRobotomy,
	createPardon
};
```

Los índices están relacionados:

```text
names[0] → create[0]
names[1] → create[1]
names[2] → create[2]
```

Por ejemplo:

```text
"robotomy request"
        ↓
names[1]
        ↓
create[1]
        ↓
createRobotomy()
        ↓
RobotomyRequestForm
```

---

# 16. Gestión de memoria

En `Intern` utilizamos:

```cpp
new
```

para crear el formulario:

```cpp
return (new RobotomyRequestForm(target));
```

Por tanto, quien recibe el puntero debe liberar la memoria:

```cpp
delete form;
```

Ejemplo:

```cpp
AForm *form;

form = intern.makeForm("robotomy request", "Bender");

if (form)
{
	// UTILIZAMOS EL FORMULARIO

	delete form;
}
```

Esto evita un memory leak.

---

# 17. Evolución completa del CPP05

```text
EX00
────
Bureaucrat
│
├── nombre
├── grado
├── incrementar grado
├── decrementar grado
└── excepciones


EX01
────
Bureaucrat
     +
Form
│
├── firmar
├── grados necesarios
└── excepciones


EX02
────
Bureaucrat
     +
AForm
     +
├── ShrubberyCreationForm
├── RobotomyRequestForm
└── PresidentialPardonForm

│
├── herencia
├── clase abstracta
├── polimorfismo
├── execute()
└── executeForm()


EX03
────
Todo lo anterior
     +
Intern
     │
     └── makeForm()
             │
             ├── Shrubbery
             ├── Robotomy
             └── Presidential Pardon
```

---

# 18. Conceptos que hay que saber explicar

Para una defensa de CPP05 deberíamos saber explicar como mínimo:

### `throw`

Lanza una excepción.

```cpp
throw GradeTooLowException();
```

### `try`

Bloque donde puede producirse una excepción.

```cpp
try
{
	form.beSigned(*this);
}
```

### `catch`

Recoge la excepción.

```cpp
catch (std::exception &e)
{
	std::cout << e.what() << std::endl;
}
```

### `what()`

Devuelve el mensaje de la excepción.

### Herencia

```cpp
class RobotomyRequestForm : public AForm
```

### Clase abstracta

Una clase que contiene al menos una función puramente virtual.

```cpp
virtual void execute(...) const = 0;
```

### Polimorfismo

Trabajar con un puntero/referencia de la clase base mientras el objeto real pertenece a una clase derivada.

### Orthodox Canonical Form

```cpp
Class();
Class(const Class &other);
Class &operator=(const Class &other);
~Class();
```

### `new` / `delete`

Crear y liberar memoria dinámicamente.

### Punteros a funciones

Utilizados en ex03 para seleccionar qué formulario crear sin una cadena enorme de `if/else if`.

---

# 19. Reglas importantes utilizadas

Todo el módulo está realizado con:

```text
C++98
-Wall
-Wextra
-Werror
```

Compilación:

```bash
c++ -Wall -Wextra -Werror -std=c++98
```

No utilizamos:

* C++11 o superior.
* `using namespace`.
* `friend`.
* `printf`.
* `malloc`.
* `free`.
* STL en este módulo.

---

# 20. Estructura final

```text
cpp05/
│
├── ex00/
│   ├── README.md
│   ├── Makefile
│   ├── main.cpp
│   ├── Bureaucrat.hpp
│   └── Bureaucrat.cpp
│
├── ex01/
│   ├── README.md
│   ├── Makefile
│   ├── main.cpp
│   ├── Bureaucrat.hpp
│   ├── Bureaucrat.cpp
│   ├── Form.hpp
│   └── Form.cpp
│
├── ex02/
│   ├── README.md
│   ├── Makefile
│   ├── main.cpp
│   ├── Bureaucrat.hpp
│   ├── Bureaucrat.cpp
│   ├── AForm.hpp
│   ├── AForm.cpp
│   ├── ShrubberyCreationForm.hpp
│   ├── ShrubberyCreationForm.cpp
│   ├── RobotomyRequestForm.hpp
│   ├── RobotomyRequestForm.cpp
│   ├── PresidentialPardonForm.hpp
│   └── PresidentialPardonForm.cpp
│
└── ex03/
    ├── README.md
    ├── Makefile
    ├── main.cpp
    ├── Bureaucrat.hpp
    ├── Bureaucrat.cpp
    ├── AForm.hpp
    ├── AForm.cpp
    ├── ShrubberyCreationForm.hpp
    ├── ShrubberyCreationForm.cpp
    ├── RobotomyRequestForm.hpp
    ├── RobotomyRequestForm.cpp
    ├── PresidentialPardonForm.hpp
    ├── PresidentialPardonForm.cpp
    ├── Intern.hpp
    └── Intern.cpp
```

---

# 21. Resumen de CPP05

La idea principal del módulo es ir construyendo un sistema de funcionarios y formularios mientras aprendemos las herramientas de C++ necesarias para gestionar errores y utilizar herencia.

```text
Bureaucrat
    ↓
puede firmar
    ↓
AForm
    ↓
formularios concretos
    ↓
pueden ejecutarse
    ↓
Intern
    ↓
crea automáticamente los formularios
```

El recorrido de aprendizaje es:

```text
EX00 → EXCEPCIONES
EX01 → EXCEPCIONES + RELACIÓN ENTRE CLASES
EX02 → HERENCIA + POLIMORFISMO + CLASE ABSTRACTA
EX03 → PUNTEROS A FUNCIONES + CREACIÓN DINÁMICA
```

**Ese es el hilo conductor de todo CPP05.**
