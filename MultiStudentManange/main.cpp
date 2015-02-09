#include "StudentManangeEngine.h"
using namespace std;
int main(int argc, char *argv[])
{
	shared_ptr<StudentManangeEngine> object(new StudentManangeEngine());

	return object->exec();
}