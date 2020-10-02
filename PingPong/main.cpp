
extern "C" int test_triangle();
extern "C" int test_triangleIOS();
extern "C" int test_testcard();
extern "C" int test_audio();
extern "C" int test_auto();
extern "C" int test_controller();

int main() {
	/*delete comment to run specific test*/

	test_auto(); // fast functional check
	//test_triangle(); // draw triangle
	//test_triangleIOS(); // draw fullscreen triangle (alt+f4 to exit)
	//test_testcard(); // some action
	//test_audio(); // sound test
	//test_controller(); //
}