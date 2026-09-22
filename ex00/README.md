El ejercicio consiste en crear una clase Bureaucrat con:

name → constante, no puede cambiar.
grade → entero entre 1 y 150.
Constructor.
Destructor.
Constructor de copia.
Operador de asignación.
getName()
getGrade()
incrementGrade()
decrementGrade()
GradeTooHighException
GradeTooLowException
operator<<

Y hay una cosa especialmente importante:

En este ejercicio empiezas a trabajar con excepciones de C++.


2. Lo primero: entender el grade
1   → máximo rango
150 → mínimo rango
grade 1
incrementGrade()
      ↓
ERROR → GradeTooHighException
grade 150
decrementGrade()
      ↓
ERROR → GradeTooLowException


3. Los atributos
¿Por qué const en _name?

Porque el enunciado dice:

A constant name.

4. Una consecuencia importante del const

Esto afecta al operator=.

Tenemos que implementar Orthodox Canonical Form porque el ejercicio lo exige para la clase.

Pero:

const std::string _name;

no se puede reasignar.

Por tanto, en:

Bureaucrat &operator=(const Bureaucrat &other);

solo podremos copiar:

_grade = other._grade;

pero no:

_name = other._name; // ❌

De hecho, el nombre queda asociado al objeto desde su construcción.


5. Las excepciones

Aquí está la parte nueva de CPP05.

Dentro de Bureaucrat podemos tener:

class GradeTooHighException : public std::exception
{
	public:
		const char *what() const throw();
};

y:

class GradeTooLowException : public std::exception
{
	public:
		const char *what() const throw();
};

La idea es que sean excepciones que podamos lanzar:

throw Bureaucrat::GradeTooHighException();

y capturar:

try
{
	// ...
}
catch (std::exception &e)
{
	std::cout << e.what() << std::endl;
}
¿Por qué heredan de std::exception?

Porque el enunciado específicamente quiere que puedan capturarse mediante:

catch (std::exception &e)

Gracias a la herencia:

std::exception
      ↑
      |
GradeTooHighException

y:

std::exception
      ↑
      |
GradeTooLowException

6. ¿Qué debe hacer el constructor?

Tenemos:

Bureaucrat("Jon", grade);

Hay tres posibilidades.

Caso válido
Bureaucrat a("Jon", 42);

Perfectamente válido.

Grade demasiado alto
Bureaucrat a("Jon", 0);

Debe lanzar:

GradeTooHighException
Grade demasiado bajo
Bureaucrat a("Jon", 151);

Debe lanzar:

GradeTooLowException

Por tanto, conceptualmente:

grade < 1
   ↓
TooHigh

1 <= grade <= 150
   ↓
OK

grade > 150
   ↓
TooLow

7. incrementGrade()

Aquí hay que tener cuidado con el nombre.

Incrementar el grado significa aumentar la categoría, por lo que numéricamente restamos 1:

3 → 2

Así que:

_grade--;

Pero antes tenemos que comprobar el límite.

Si:

_grade == 1

no podemos hacer:

_grade--;

porque terminaríamos en 0.

Debe lanzar:

throw GradeTooHighException();
8. decrementGrade()

Al contrario:

3 → 4

Por tanto:

_grade++;

Pero si estamos en:

150

no podemos pasar a:

151

y debemos lanzar:

GradeTooLowException

9. operator<<

El resultado tiene que ser exactamente:

<name>, bureaucrat grade <grade>.

Por ejemplo:

Jon, bureaucrat grade 42.

La firma será:

std::ostream &operator<<(std::ostream &out, const Bureaucrat &bureaucrat);

Y devolveremos:

return out;

Esto es importante porque queremos poder hacer:

std::cout << bureaucrat << std::endl;

/*se llama a e.what porq es asi por norma,
 y lueago el programa a ver si nos pasams de numero 
 para abajo o para arriba decide aq throw va*/

 /*Crear un funcionario que tenga un nombre y un grado
limitado entre 1 y 150, que pueda subir/bajar de grado
y que lance excepciones cuando intente salirse de esos límites*/