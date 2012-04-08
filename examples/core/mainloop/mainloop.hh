#include <xfc/glib/error.hh>
#include <xfc/glib/iochannel.hh>
#include <xfc/glib/main.hh>
#include <xfc/glib/thread.hh>

using namespace Xfc;

struct AddrData;
struct TestData;

class MainLoopTest : public G::MainLoop
{
	static bool adder_response(G::IOConditionField condition, G::IOChannel *channel, TestData *test_data);
	static bool adder_callback(G::IOConditionField condition, G::IOChannel *channel, AddrData *addr_data);
	static bool timeout_callback(AddrData *addr_data);

	static int crawler_callback(G::Source* source);
	static void cleanup_crawlers(G::MainContext *context);
	static void remove_crawler();

	static void do_add(G::IOChannel *in, int a, int b);
	static void io_pipe(G::IOChannel **channels);
	static bool recurser_idle(G::MainContext *context);

	static bool read_all(G::IOChannel *channel, char *buffer, gsize length);
	static bool write_all(G::IOChannel *channel, char *buffer, gsize length);

public:
	MainLoopTest();
	~MainLoopTest();

	void create_adder_thread();
	void adder_thread(G::IOChannel **channels);

	static void create_crawler();
	static bool recurser_start();
};

