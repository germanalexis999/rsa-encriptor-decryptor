Laboratorio N° 3 - Sistemas Operativos II: Cifrado y Descifrado de Palabra Clave en Imagen BMP utilizando RSA
Este laboratorio tiene como objetivo implementar un sistema de cifrado y descifrado utilizando el algoritmo RSA, aplicado a una palabra clave oculta dentro de una imagen BMP. El proceso incluye la extracción de la clave oculta, su encriptación usando RSA y finalmente su desencriptación para validar el funcionamiento del algoritmo.

Descripción del Proyecto
Este proyecto realiza los siguientes pasos:

Extracción de palabra clave oculta: Se extrae una palabra clave oculta en una imagen BMP. Esta palabra clave fue previamente cifrada.
Cifrado RSA: La palabra clave extraída se encripta utilizando el algoritmo RSA.
Desencriptado RSA: La palabra clave cifrada se desencripta utilizando las claves privadas y públicas generadas con RSA para verificar que el proceso de encriptación y desencriptación se realiza correctamente.
El proyecto hace uso de la librería GMP (GNU Multiple Precision Arithmetic) para manejar números grandes, lo que es esencial para las operaciones matemáticas en el algoritmo RSA.

Requisitos
1. Instalar la librería GMP:
La librería GMP es esencial para el manejo de enteros grandes necesarios en RSA. Si no la tienes instalada, puedes hacerlo en sistemas basados en Debian/Ubuntu con el siguiente comando:

bash
Copiar código
sudo apt-get install libgmp-dev
2. Instalar GCC:
Asegúrate de tener el compilador GCC instalado en tu sistema para poder compilar el código fuente en C.

Instrucciones de Compilación y Ejecución
Paso 1: Compilar los archivos fuente
El proyecto consta de dos archivos principales:

bmpdecryptor.c: Este archivo contiene la lógica para extraer la palabra clave cifrada desde una imagen BMP.
encryptor-decryptor.c: Este archivo realiza el cifrado y desencriptado de la palabra clave utilizando RSA.
Para compilar ambos archivos, debes usar el siguiente comando:

bash
Copiar código
gcc -o encryptor-decryptor encryptor-decryptor.c -lgmp
Este comando generará un archivo ejecutable llamado encryptor-decryptor, que podrás utilizar para ejecutar el programa.

PD: bmpdecryptor.c no requiere la libreria -lgmp

Paso 2: Ejecutar el programa
Para ejecutar el programa, debes proporcionar el nombre de una imagen BMP que contenga un mensaje cifrado.  Asegúrate de estar en el directorio raíz del proyecto.


Extraerá la palabra clave de la imagen BMP.
Cifrará la palabra clave usando el algoritmo RSA.
Desencriptará la palabra clave cifrada para verificar que el proceso de cifrado y descifrado se realiza correctamente.
Descripción de Archivos
bmpdecryptor.c: Este archivo contiene la lógica para extraer la palabra clave cifrada desde la imagen BMP. Este script lee el archivo BMP y decodifica la palabra clave que fue ocultada en su estructura.
encryptor-decryptor.c: Contiene la implementación de la encriptación y desencriptación de la palabra clave utilizando el algoritmo RSA, así como la gestión de claves públicas y privadas.
Imagen BMP: La imagen BMP debe contener un mensaje cifrado en su estructura. El mensaje extraído será encriptado y luego desencriptado.
Flujo del Proyecto
Extracción de la palabra clave: El programa lee la imagen BMP y extrae la palabra clave oculta en ella utilizando el script bmpdecryptor.c.
Cifrado de la palabra clave: La palabra clave extraída es cifrada usando el algoritmo RSA con una clave pública generada.
Desencriptado: La palabra clave cifrada se desencripta utilizando la clave privada para validar que el proceso de cifrado y descifrado funciona correctamente.
Notas
Dependencia de GMP: Este proyecto depende de la librería GMP para manejar enteros grandes necesarios para las operaciones del algoritmo RSA.
Imagen BMP: La imagen debe tener la palabra clave cifrada oculta dentro de su estructura. La imagen debe estar en formato BMP.