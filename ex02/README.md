# CPP05 — ex02

## 1. ¿Qué pide realmente el ejercicio?

En `ex01` teníamos:

```text
Bureaucrat
    |
    └── Form
```

En `ex02` pasamos a tener:

```text
                 AForm
              /    |    \
             /     |     \
      Shrubbery  Robotomy  Presidential
```

`AForm` significa **Abstract Form**.

La idea es:

* `AForm` → contiene la lógica común de los formularios.
* `ShrubberyCreationForm` → crea un archivo con árboles ASCII.
* `RobotomyRequestForm` → intenta robotizar al objetivo.
* `PresidentialPardonForm` → anuncia un indulto.
* `Bureaucrat` → puede firmar y ejecutar formularios.

### Resumen en una frase

> Crear una clase abstracta `AForm` y tres formularios concretos que, una vez firmados y ejecutados por un `Bureaucrat` con grado suficiente, realizan distintas acciones.

---

# 2. ¿Qué cambia respecto a ex01?

## En ex01

Teníamos:

```cpp
class Form
```

con:

```text
_name
_signed
_gradeToSign
_gradeToExecute
```

Y la función:

```cpp
beSigned()
```

## En ex02

`Form` desaparece y pasa a llamarse:

```cpp
class AForm
```

Además añadimos:

```cpp
virtual void execute(Bureaucrat const &executor) const = 0;
```

El `= 0` hace que `execute()` sea una **función virtual pura**.

Por eso `AForm` se convierte en una **clase abstracta**.

No podemos hacer:

```cpp
AForm form(...);
```

Las clases que sí podemos crear son:

```cpp
ShrubberyCreationForm
RobotomyRequestForm
PresidentialPardonForm
```

---

# 3. ¿Qué es una clase abstracta?

Una clase abstracta es una clase que sirve como **base para otras clases**, pero que no podemos crear directamente.

En nuestro caso:

```text
AForm
  |
  ├── ShrubberyCreationForm
  ├── RobotomyRequestForm
  └── PresidentialPardonForm
```

`AForm` contiene lo que todos los formularios tienen en común.

Cada formulario concreto se encarga de hacer su propia acción.

---

# 4. Los tres formularios

| Formulario               | Firmar | Ejecutar | Acción                     |
| ------------------------ | -----: | -------: | -------------------------- |
| `ShrubberyCreationForm`  |    145 |      137 | Crea `<target>_shrubbery`  |
| `RobotomyRequestForm`    |     72 |       45 | Robotomía con 50% de éxito |
| `PresidentialPardonForm` |     25 |        5 | Indulta al target          |

Recuerda:

```text
1   = mejor grado
150 = peor grado
```

Por ejemplo:

```cpp
RobotomyRequestForm form("Bender");
```

Crea un formulario cuyo objetivo es:

```text
Bender
```

---

# 5. ¿Qué significa `_target`?

Cada formulario tiene:

```cpp
std::string _target;
```

Es el objetivo sobre el que se realizará la acción.

Por ejemplo:

```cpp
ShrubberyCreationForm form("home");
```

Entonces:

```text
_target = "home"
```

Y al ejecutarlo correctamente se crea:

```text
home_shrubbery
```

Otro ejemplo:

```cpp
RobotomyRequestForm form("Bender");
```

El objetivo de la robotomía es:

```text
Bender
```

---

# 6. ¿Qué comprueba `execute()`?

Antes de realizar la acción hay que comprobar dos cosas.

## 1. El formulario está firmado

```text
¿Está firmado?
     |
    NO → excepción
     |
    SÍ
```

## 2. El Bureaucrat tiene suficiente grado

Por ejemplo:

```text
RobotomyRequestForm
necesita grado 45
```

Un Bureaucrat de grado:

```text
30 → puede ejecutar
60 → no puede ejecutar
```

Porque:

```text
1 = mejor
150 = peor
```

---

# 7. ¿Dónde hacemos las comprobaciones?

El ejercicio permite hacer las comprobaciones en `AForm` o en los formularios concretos.

Nosotros las hacemos **en cada formulario concreto**, porque es más sencillo.

Por ejemplo:

```cpp
void ShrubberyCreationForm::execute(
	Bureaucrat const &executor) const
{
	// COMPRUEBA QUE ESTÉ FIRMADO
	if (!getSigned())
		throw std::exception();

	// COMPRUEBA EL GRADO
	if (executor.getGrade() > getGradeToExecute())
		throw std::exception();

	// REALIZA LA ACCIÓN
}
```

Cada formulario hace:

```text
execute()
   |
   ├── ¿Está firmado?
   |       NO → excepción
   |
   ├── ¿Tiene grado suficiente?
   |       NO → excepción
   |
   └── SÍ → realiza su acción
```

No necesitamos una función adicional como `executeAction()`.

---

# 8. ¿Qué hace `Bureaucrat::executeForm()`?

En `ex01` teníamos:

```cpp
bureaucrat.signForm(form);
```

Ahora añadimos:

```cpp
bureaucrat.executeForm(form);
```

El flujo es:

```text
Bureaucrat
     |
     v
executeForm(form)
     |
     v
form.execute(*this)
     |
     ├── OK → realiza la acción
     |
     └── error → catch
```

Por ejemplo:

```cpp
boss.executeForm(shrubbery);
```

Si funciona:

```text
Boss executed ShrubberyCreationForm
```

Si falla:

```text
Boss couldn't execute ShrubberyCreationForm because ...
```

---

# 9. ShrubberyCreationForm

Necesita:

```text
145 → firmar
137 → ejecutar
```

Ejemplo:

```cpp
ShrubberyCreationForm form("home");
```

Si está firmado y se ejecuta correctamente:

```text
home_shrubbery
```

Se crea en el directorio de trabajo actual.

Dentro se escriben **árboles ASCII**.

Por ejemplo:

```text
       /\
      /  \
     /    \
    /____\
      ||
      ||
```

---

# 10. RobotomyRequestForm

Necesita:

```text
72 → firmar
45 → ejecutar
```

Ejemplo:

```cpp
RobotomyRequestForm form("Bender");
```

Al ejecutarlo correctamente:

```text
* drilling noises *
```

Después hay aproximadamente un:

```text
50% → éxito
50% → fracaso
```

Si tiene éxito:

```text
Bender has been robotomized successfully
```

Si falla:

```text
The robotomy failed on Bender
```

Para generar el resultado usamos:

```cpp
std::rand() % 2
```

Que nos permite obtener:

```text
0
1
```

y utilizarlo como resultado 50/50.

---

# 11. PresidentialPardonForm

Necesita:

```text
25 → firmar
5  → ejecutar
```

Ejemplo:

```cpp
PresidentialPardonForm form("Jon");
```

Si está firmado y se ejecuta correctamente:

```text
Jon has been pardoned by Zaphod Beeblebrox.
```

---

# 12. Archivos del ejercicio

La estructura final es:

```text
ex02/
│
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
└── PresidentialPardonForm.cpp
```

---

# 13. Orthodox Canonical Form

Las clases siguen la Orthodox Canonical Form.

Tenemos:

```cpp
Constructor por defecto
Constructor de copia
Operador de asignación
Destructor
```

Por ejemplo:

```cpp
ShrubberyCreationForm();
ShrubberyCreationForm(const ShrubberyCreationForm &other);
ShrubberyCreationForm &operator=(
	const ShrubberyCreationForm &other);
~ShrubberyCreationForm();
```

En nuestro caso el constructor real recibe el `target`, pero seguimos teniendo constructor de copia, asignación y destructor.

---

# 14. Herencia

Los formularios concretos heredan de `AForm`:

```cpp
class ShrubberyCreationForm : public AForm
```

```cpp
class RobotomyRequestForm : public AForm
```

```cpp
class PresidentialPardonForm : public AForm
```

Esto significa que todos tienen las características comunes de `AForm`.

Por ejemplo:

```cpp
getName()
getSigned()
getGradeToSign()
getGradeToExecute()
beSigned()
```

Y cada uno implementa:

```cpp
execute()
```

de una forma diferente.

---

# 15. `virtual ... = 0`

En `AForm.hpp` tenemos:

```cpp
virtual void execute(Bureaucrat const &executor) const = 0;
```

El:

```cpp
= 0
```

significa que es una **función virtual pura**.

Esto obliga a las clases hijas a implementar `execute()`.

Por ejemplo:

```cpp
ShrubberyCreationForm::execute()
```

hace una cosa.

```cpp
RobotomyRequestForm::execute()
```

hace otra.

```cpp
PresidentialPardonForm::execute()
```

hace otra.

---

# 16. Include guards

Todos nuestros `.hpp` tienen include guards:

```cpp
#ifndef AFORM_HPP
#define AFORM_HPP

// código

#endif
```

Esto evita que el mismo header se incluya varias veces.

---

# 17. Reglas de compilación

El ejercicio debe compilar con:

```bash
c++ -Wall -Wextra -Werror
```

Y también debe funcionar con:

```bash
c++ -Wall -Wextra -Werror -std=c++98
```

Por tanto, no utilizamos características de C++11 o posteriores.

No utilizamos:

```text
auto
nullptr
override
```

ni otras características modernas.

---

# 18. Cosas prohibidas

En este módulo no podemos u
