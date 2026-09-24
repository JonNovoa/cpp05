# CPP05 — ex00

## 1. ¿Qué pide realmente el ejercicio?

En `ex00` tenemos que crear una clase llamada `Bureaucrat`.

La clase representa a un funcionario que tiene:

```text
nombre
grado
```

El grado va del:

```text
1 → mejor grado
150 → peor grado
```

El objetivo principal del ejercicio es practicar:

* Clases.
* Excepciones.
* Constructores.
* Orthodox Canonical Form.
* Sobrecarga de `operator<<`.
* Control de límites.

---

# 2. Clase Bureaucrat

La clase tiene dos atributos privados:

```cpp
const std::string _name;
int _grade;
```

`_name` es el nombre del funcionario.

`_grade` es su grado.

Por ejemplo:

```cpp
Bureaucrat bob("Bob", 50);
```

Tenemos:

```text
Nombre → Bob
Grado  → 50
```

---

# 3. Los grados

Los grados válidos son:

```text
1 - 150
```

Importante:

```text
1   = mejor
150 = peor
```

Por tanto:

```text
Bob, grade 10
```

tiene un grado mejor que:

```text
Bob, grade 100
```

---

# 4. Constructor

El constructor recibe:

```cpp
Bureaucrat(const std::string &name, int grade);
```

Comprueba que el grado sea válido.

Si:

```text
grade < 1
```

se lanza:

```cpp
GradeTooHighException
```

Si:

```text
grade > 150
```

se lanza:

```cpp
GradeTooLowException
```

---

# 5. Excepciones

Tenemos dos excepciones dentro de `Bureaucrat`.

## GradeTooHighException

Se produce cuando el grado es demasiado alto.

Por ejemplo:

```cpp
Bureaucrat bob("Bob", 0);
```

No puede existir porque el mejor grado permitido es `1`.

---

## GradeTooLowException

Se produce cuando el grado es demasiado bajo.

Por ejemplo:

```cpp
Bureaucrat bob("Bob", 151);
```

No puede existir porque el peor grado permitido es `150`.

---

# 6. Subir de grado

Tenemos:

```cpp
void incrementGrade();
```

Aquí ocurre algo importante:

**subir de grado significa reducir el número.**

Por ejemplo:

```text
50 → 49
```

Porque:

```text
49 es mejor que 50
```

Si estamos en:

```text
1
```

no podemos subir más.

Entonces se lanza:

```cpp
GradeTooHighException
```

---

# 7. Bajar de grado

Tenemos:

```cpp
void decrementGrade();
```

Aquí aumentamos el número:

```text
50 → 51
```

Si estamos en:

```text
150
```

no podemos bajar más.

Entonces se lanza:

```cpp
GradeTooLowException
```

---

# 8. Orthodox Canonical Form

La clase tiene:

```cpp
Bureaucrat();
Bureaucrat(const Bureaucrat &other);
Bureaucrat &operator=(const Bureaucrat &other);
~Bureaucrat();
```

Es decir:

1. Constructor por defecto.
2. Constructor de copia.
3. Operador de asignación.
4. Destructor.

---

# 9. Getters

Tenemos:

```cpp
const std::string &getName() const;
int getGrade() const;
```

Sirven para consultar:

```text
nombre
grado
```

sin modificar el objeto.

---

# 10. operator<<

Podemos hacer:

```cpp
std::cout << bob;
```

Y obtenemos algo como:

```text
Bob, bureaucrat grade 50.
```

Esto se consigue sobrecargando:

```cpp
operator<<
```

---

# 11. Resumen

`Bureaucrat` representa un funcionario con:

```text
Nombre
Grado
```

El grado siempre debe estar entre:

```text
1 y 150
```

Y tenemos que controlar correctamente los límites al crear el objeto y al subir/bajar de grado.

---

## Frase para memorizar

> **Bureaucrat es una clase que representa un funcionario con un nombre y un grado entre 1 y 150, utilizando excepciones para controlar los límites del grado.**
