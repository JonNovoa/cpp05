# CPP05 — ex03

## At least this beats coffee-making

---

## 1. ¿Qué pide el ejercicio?

En los ejercicios anteriores hemos creado:

* `Bureaucrat`
* `AForm`
* `ShrubberyCreationForm`
* `RobotomyRequestForm`
* `PresidentialPardonForm`

En este ejercicio aparece una nueva clase:

```text
Intern
```

El `Intern` es un becario que se encarga de crear formularios para los `Bureaucrat`.

El `Intern` no tiene:

* nombre
* grado
* atributos propios

Su única función importante es:

```cpp
AForm *makeForm(const std::string &formName,
				const std::string &target);
```

Recibe:

1. El nombre del formulario que queremos crear.
2. El objetivo del formulario.

Y devuelve un puntero a `AForm`.

---

# 2. ¿Qué debe hacer `makeForm()`?

Por ejemplo:

```cpp
Intern intern;

AForm *form;

form = intern.makeForm("robotomy request", "Bender");
```

El `Intern` debe reconocer:

```text
"robotomy request"
```

y crear:

```cpp
RobotomyRequestForm("Bender");
```

Aunque realmente se crea un `RobotomyRequestForm`, se devuelve como:

```cpp
AForm *
```

Esto funciona porque `RobotomyRequestForm` hereda de `AForm`.

---

# 3. Formularios disponibles

El `Intern` conoce estos tres formularios:

| Nombre recibido       | Formulario creado        |
| --------------------- | ------------------------ |
| `shrubbery creation`  | `ShrubberyCreationForm`  |
| `robotomy request`    | `RobotomyRequestForm`    |
| `presidential pardon` | `PresidentialPardonForm` |

Por ejemplo:

```cpp
intern.makeForm("shrubbery creation", "home");
```

crea:

```cpp
ShrubberyCreationForm("home");
```

---

# 4. Mensaje al crear un formulario

Cuando el formulario existe, el `Intern` debe mostrar:

```text
Intern creates robotomy request
```

Después devuelve el formulario creado.

---

# 5. Formulario inexistente

Si hacemos:

```cpp
intern.makeForm("pizza", "Bender");
```

ese formulario no existe.

El `Intern` debe mostrar un mensaje de error y devolver:

```cpp
NULL
```

---

# 6. No utilizar un `if/else if` enorme

El enunciado indica expresamente que no debemos hacer una solución llena de:

```cpp
if (...)
else if (...)
else if (...)
else if (...)
```

Por eso utilizamos dos arrays relacionados.

Uno contiene los nombres:

```cpp
std::string names[3] =
{
	"shrubbery creation",
	"robotomy request",
	"presidential pardon"
};
```

Y otro contiene las funciones que crean cada formulario:

```cpp
AForm *(*create[3])(const std::string &) =
{
	createShrubbery,
	createRobotomy,
	createPardon
};
```

De esta forma:

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

# 7. Funciones de creación

Tenemos tres funciones auxiliares:

```cpp
AForm *createShrubbery(const std::string &target)
{
	return (new ShrubberyCreationForm(target));
}
```

```cpp
AForm *createRobotomy(const std::string &target)
{
	return (new RobotomyRequestForm(target));
}
```

```cpp
AForm *createPardon(const std::string &target)
{
	return (new PresidentialPardonForm(target));
}
```

Cada una crea el formulario correspondiente y devuelve un `AForm *`.

---

# 8. ¿Por qué `AForm *`?

Porque los tres formularios heredan de `AForm`:

```text
                 AForm
                /  |  \
               /   |   \
      Shrubbery  Robotomy  Presidential
```

Por tanto podemos hacer:

```cpp
AForm *form = new RobotomyRequestForm("Bender");
```

y después utilizar:

```cpp
boss.signForm(*form);
boss.executeForm(*form);
```

El polimorfismo hace que se utilice el comportamiento correspondiente al formulario real.

---

# 9. Intern no tiene atributos

El `Intern` es muy sencillo:

```cpp
class Intern
{
	public:
		Intern();
		Intern(const Intern &other);
		Intern &operator=(const Intern &other);
		~Intern();

		AForm *makeForm(const std::string &formName,
			const std::string &target);
};
```

No tiene variables privadas porque el enunciado dice que el `Intern` no tiene características propias.

Aun así implementamos el Orthodox Canonical Form porque estamos en los ejercicios donde se pide.

---

# 10. Flujo completo

El funcionamiento del ejercicio es:

```text
Intern
  │
  │ makeForm("robotomy request", "Bender")
  ↓
Busca el nombre
  │
  ↓
Encuentra "robotomy request"
  │
  ↓
createRobotomy("Bender")
  │
  ↓
RobotomyRequestForm
  │
  ↓
AForm *
  │
  ↓
Bureaucrat
  │
  ├── signForm()
  │
  └── executeForm()
```

---

# 11. Prueba realizada

Nuestro `main.cpp` prueba:

```cpp
Intern someRandomIntern;

AForm *form;

form = someRandomIntern.makeForm("robotomy request", "Bender");
```

Después:

```cpp
Bureaucrat boss("Boss", 1);

boss.signForm(*form);
boss.executeForm(*form);
```

La salida obtenida fue:

```text
Intern creates robotomy request
Boss signed RobotomyRequestForm
* drilling noises *
The robotomy failed on Bender
Boss executed RobotomyRequestForm
```

El fallo de la robotomía es normal porque tiene un **50% de posibilidades de éxito**.

---

# 12. Archivos de ex03

```text
ex03/
├── Makefile
├── main.cpp
│
├── Bureaucrat.hpp
├── Bureaucrat.cpp
│
├── AForm.hpp
├── AForm.cpp
│
├── ShrubberyCreationForm.hpp
├── ShrubberyCreationForm.cpp
│
├── RobotomyRequestForm.hpp
├── RobotomyRequestForm.cpp
│
├── PresidentialPardonForm.hpp
├── PresidentialPardonForm.cpp
│
├── Intern.hpp
└── Intern.cpp
```

Los archivos de `Bureaucrat`, `AForm` y los tres formularios son los mismos que en `ex02`.

En `ex03` añadimos:

```text
Intern.hpp
Intern.cpp
```

y modificamos:

```text
main.cpp
Makefile
```

para probar e incluir el nuevo `Intern`.

---

# 13. Conceptos importantes para defender

### Herencia

Los formularios concretos heredan de `AForm`.

### Polimorfismo

Podemos guardar un:

```cpp
RobotomyRequestForm *
```

como:

```cpp
AForm *
```

### Punteros a funciones

Utilizamos:

```cpp
AForm *(*create[3])(const std::string &)
```

para guardar las funciones que crean cada formulario.

### `new`

El formulario se crea dinámicamente:

```cpp
return (new RobotomyRequestForm(target));
```

Por eso quien recibe el puntero debe encargarse posteriormente de liberarlo:

```cpp
delete form;
```

### `NULL`

Si el nombre del formulario no existe:

```cpp
return (NULL);
```

Así indicamos que no se ha podido crear ningún formulario.

---

## Resumen

**ex02:** tenemos los formularios y podemos firmarlos/ejecutarlos.

**ex03:** añadimos un `Intern` capaz de crear automáticamente cualquiera de esos formularios a partir de su nombre.

La parte nueva e importante es:

```cpp
AForm *makeForm(...)
```

y la utilización de **punteros a funciones** para evitar una solución basada en una cadena de `if/else if`.
