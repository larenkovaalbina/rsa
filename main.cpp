#include "RSA.h"
#include <iostream>

int main()
{
	cout << "start" << endl;
	RSA tryhard;
	BigInteger message(1234567890);
	
	cout <<"message:   "<< message << endl;
	BigInteger crypt, result, e, n;
	tryhard.publish_keys(e, n);
	cout << "exp:  " << e << endl << "key:  " << n << endl;
	tryhard.encryption(message, crypt);
	cout << "crypted message:  " << crypt << endl;
	tryhard.decryption(result, crypt);
	cout << "decrypted message:   " << result << endl;
	system("pause");
	return 0;
}



