#include "MultiClientChat.h"


void main()
{
	MultiClientChat mcc("0.0.0.0", 54000);
	if (mcc.init() != 0)
		return;

	mcc.run();

	system("pause");
}