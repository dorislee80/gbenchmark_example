#include <benchmark/benchmark.h>
#include <stdlib.h>


static const int RECEIVED = 1;
static const int CONNECTED = 2;
static const int DISCONNECTED = 3;
static const int SENT = 4;
static const int CAUGHT = 5;
static const int CONNECTING = 6;
static const int DISCONNECTING = 7;


struct ChannelState {
    int state;
};


class BranchSwitchFixture : public benchmark::Fixture {
public:
    BranchSwitchFixture() : states(new ChannelState[10000]) {
    }

    ~BranchSwitchFixture() {
      delete[] states;
    }


    // Initialize elements in the array of 'states'. SetUp
    // makes sure more than 99.99% elements have state 'RECEIVED'
    // so that we can measure how CPU's branch prediction affect
    // performance.
    void SetUp(const benchmark::State& st) {
      int threshold = RAND_MAX / 10000;

      for (int i = 0; i < 10000; i++) {
        int r = rand();
        if (r > threshold)
          states[i].state = RECEIVED;
        else {
          states[i].state = (r % 6) + 2;
        }
      }
    }

    void TearDown(const benchmark::State&) { }


    ChannelState* states;
};


// Blackhole copies the value to an integer allocated
// in the heap. Its purpose to prevent the compiler
// from optimizing the benchmark loop.
class BlackHole {
    int* data;

public:
    BlackHole() : data(new int(0)) { }
    ~BlackHole() {
      delete data;
    }

    void consume(int v) {
      *data = v;
    }
};

BlackHole bh;


BENCHMARK_F(BranchSwitchFixture, BenchSwitch)(benchmark::State& state) {
  int result = 0;

  for (auto _ : state) {
      for (int i = 0; i < 10000; i++)
        switch (states[i].state)
        {
          case RECEIVED:
            result += states[i].state;
            break;
          case CONNECTED:
            result += states[i].state;
            break;
          case DISCONNECTED:
            result += states[i].state;
            break;
          case SENT:
            result += states[i].state;
            break;
          case CAUGHT:
            result += states[i].state;
            break;
          case CONNECTING:
            result += states[i].state;
            break;
          case DISCONNECTING:
            result += states[i].state;
            break;
        }
  }          

  bh.consume(result);
}


BENCHMARK_F(BranchSwitchFixture, BenchIfSwitch)(benchmark::State& state) {
  int result = 0;

  for (auto _ : state) {
    for (int i = 0; i < 10000; i++)
      // Simple does "if (states[i].state == RECEIVED)" doesn't trigger 
      // the branch prediction optimization  
      if (__builtin_expect(states[i].state == RECEIVED, true))
        result += states[i].state;
      else {
        switch (states[i].state) {
          case CONNECTED:
            result += states[i].state;
            break;
          case DISCONNECTED:
            result += states[i].state;
            break;
          case SENT:
            result += states[i].state;
            break;
          case CAUGHT:
            result += states[i].state;
            break;
          case CONNECTING:
            result += states[i].state;
            break;
          case DISCONNECTING:
            result += states[i].state;
            break;
        }
      }
  }

  bh.consume(result);
}


BENCHMARK_MAIN();
