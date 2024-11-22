Laboratorio N 3 de Sistemas operativos II, en el cual se descifra una palabra clave oculta en una imagen BMP y luego se procede a encriptar la misma utilizando el algoritmos de encriptacion RSA y su correspondiente Desencriptacion


bmpdecryptor

simplemente compilar e ingresar el nombre de la iamgen con codigo encritado con su tipo de archivo en este caso bmp

Compilar encryptor-decryptor.c 

como hacemos uso de la libreria GMP para poder tener enteros con precision de mas de 8 bytes se debe hacer el llamado a la librery para compliar 


gc -o encryptor-decryptor encryptor-decryptor.c -lgmp

ejecutar ( dentro de la raiz )

./ encryptor-decryptor