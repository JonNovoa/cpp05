# CPP05 — ex01

## 1. ¿Qué añade este ejercicio?

En `ex00` solamente teníamos:

```text
Bureaucrat
```

Ahora añadimos:

```text
Form
```

La relación es:

```text
Bureaucrat
     |
     | puede firmar
     v
   Form
```

El objetivo es practicar la relación entre clases y el uso de excepciones.

---

# 2. Clase Form

`Form` representa un formulario que tiene:

```text
nombre
firmado / no firmado
grado necesario para firmar
grado necesario para ejecutar
```

Sus atributos son:

```cpp
const std::string _name;
bool _signed;
const int _gradeToSign;
const int _gradeToExecute;
```

---

# 3. Grados del formulario

Al igual que en `Bureaucrat`:

```text
1   = mejor
150 = peor
```

El formulario tiene dos grados diferentes:

```text
gradeToSign
gradeToExecute
```

Por ejemplo:

```cpp
Form contract("Contract", 50, 30);
```

Significa:

```text
50 → necesita grado 50 o mejor para firmar
30 → necesita grado 30 o mejor para ejecutar
```

---

# 4. Crear un formulario

Ejemplo:

```cpp
Form contract("Contract", 50, 30);
```

Inicialmente:

```text
signed = no
```

Por tanto:

```text
Contract
signed: no
grade required to sign: 50
grade required to execute: 30
```

---

# 5. Firmar un formulario

Tenemos:

```cpp
void beSigned(const Bureaucrat &bureaucrat);
```

Esta función comprueba si el Bureaucrat tiene suficiente grado.

Por ejemplo:

```text
Form necesita 50
Bureaucrat tiene 40
```

Como:

```text
40 es mejor que 50
```

puede firmarlo.

Resultado:

```text
signed = yes
```

---

# 6. Cuando no puede firmar

Por ejemplo:

```text
Form necesita 50
Bureaucrat tiene 60
```

Como:

```text
60 es peor que 50
```

no puede firmarlo.

Se lanza:

```cpp
GradeTooLowException
```

---

# 7. Bureaucrat::signForm()

Añadimos a `Bureaucrat`:

```cpp
void signForm(Form &form);
```

Esto permite hacer:

```cpp
bob.signForm(contract);
```

Internamente intenta:

```cpp
form.beSigned(*this);
```

Si puede:

```text
Bob signed Contract
```

Si no puede:

```text
Bob couldn't sign Contract because Form grade is too low!
```

El `try/catch` está dentro de `signForm()` para que el programa pueda mostrar el error sin terminar.

---

# 8. ¿Qué significa `*this`?

Dentro de:

```cpp
Bureaucrat::signForm()
```

`this` representa al objeto actual.

Por tanto:

```cpp
*this
```

significa:

> el propio Bureaucrat que está ejecutando `signForm()`.

Por ejemplo:

```cpp
bob.signForm(form);
```

hace conceptualmente:

```cpp
form.beSigned(bob);
```

---

# 9. Orthodox Canonical Form

Tanto `Bureaucrat` como `Form` siguen la Orthodox Canonical Form.

Tenemos:

```cpp
Constructor por defecto
Constructor de copia
Operador de asignación
Destructor
```

---

# 10. Atributos const

Tenemos:

```cpp
const std::string _name;
const int _gradeToSign;
const int _gradeToExecute;
```

Estos valores no pueden cambiar después de crear el objeto.

Por eso el operador de asignación solamente puede modificar:

```cpp
_signed
```

Por ejemplo:

```cpp
Form &Form::operator=(const Form &other)
{
	if (this != &other)
		_signed = other._signed;
	return (*this);
}
```

---

# 11. Sobrecarga de operator<<

Podemos hacer:

```cpp
std::cout << form;
```

Y obtener:

```text
Contract, signed: yes, grade required to sign: 50, grade required to execute: 30
```

---

# 12. Excepciones de Form

`Form` tiene:

```cpp
GradeTooHighException
GradeTooLowException
```

Se utilizan al crear un formulario con grados fuera de:

```text
1 - 150
```

Por ejemplo:

```cpp
Form form("Test", 0, 30);
```

produce:

```text
Form grade is too high!
```

Y:

```cpp
Form form("Test", 50, 151);
```

produce:

```text
Form grade is too low!
```

---

# 13. Lo que hay que entender

La idea principal de `ex01` es:

```text
                Bureaucrat
                    |
                    | signForm()
                    v
                   Form
                    |
                    | beSigned()
                    v
             ¿grado suficiente?
                /        \
              NO          SÍ
              |            |
           excepción     firmado
```

El `Bureaucrat` intenta firmar el formulario.

El propio `Form` comprueba si el grado es suficiente.

---

# 14. Ejemplo completo

Tenemos:

```cpp
Bureaucrat bob("Bob", 40);
Form contract("Contract", 50, 30);
```

Bob tiene grado:

```text
40
```

El formulario necesita:

```text
50 para firmar
```

Como:

```text
40 < 50
```

Bob puede firmarlo.

Hacemos:

```cpp
bob.signForm(contract);
```

Resultado:

```text
Bob signed Contract
```

El formulario pasa de:

```text
signed: no
```

a:

```text
signed: yes
```

---

# 15. Diferencia importante entre firmar y ejecutar

En `ex01` el formulario **ya tiene**:

```cpp
_gradeToExecute
```

pero todavía no tenemos una función para ejecutarlo.

Es decir:

```text
ex01
   |
   ├── puede comprobar quién puede firmar
   |
   └── guarda quién debería poder ejecutar
```

La ejecución real llegará en:

```text
ex02
```

donde `Form` se convierte en:

```text
AForm
```

y aparecen:

```cpp
execute()
executeForm()
```

---

## Frase para memorizar

> **Form representa un documento que puede estar firmado y que tiene un grado mínimo necesario para firmarlo y otro para ejecutarlo. Bureaucrat puede intentar firmarlo mediante `signForm()`.**
