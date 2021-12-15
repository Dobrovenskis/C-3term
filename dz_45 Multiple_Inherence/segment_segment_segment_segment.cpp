#include <iostream>
#include <set>
#include <random>
#include <vector>

class GeneralState
{
public:
    virtual bool contains(int s) const{}
};

class DiscreteState: public GeneralState {
private:
    int const state;

public:
    DiscreteState(int state): state(state) { }

    bool contains(int s) const {
        return s == state;
    }
};

class SegmentState: virtual public GeneralState {
private:
    int const beg, end;

public:
    SegmentState(): SegmentState(0, -1) { }//beg(0), end(-1) { }
    SegmentState(int beg, int end): beg(beg), end(end) { }

    bool contains(int s) const {
        return s >= beg && s <= end;
    }
};

class SetState: virtual public GeneralState {
private:
    std::set<int> const states;

public:
    SetState(): states() { }
    SetState(std::set<int> const &src): states(src) { }

    bool contains(int s) const {
        return states.count(s) > 0;
    }
};

class SegmentAndDots:  public SegmentState, public SetState
{
public:
    SegmentAndDots(): SetState(), SegmentState(){};
    SegmentAndDots(int beg, int end, std::set<int> states): SetState(states), SegmentState(beg, end) {};

    bool contains(int s) const {
        bool ret = SetState::contains(s) || SegmentState::contains(s);
        return ret;
    }
};

class Segment_and_delete_discrete_state: public SegmentState, public SetState
{
public:
    Segment_and_delete_discrete_state(): SetState(), SegmentState(){};
    Segment_and_delete_discrete_state(int beg, int end, std::set<int> states): SetState(states), SegmentState(beg, end) {};

    bool contains(int s) const {
        bool ret = SetState::contains(s) && (!SegmentState::contains(s));
        return ret;
    }

};

class ProbabilityTest {
private:
    unsigned seed;
    int test_min, test_max;
    unsigned test_count;

public:
    ProbabilityTest(unsigned seed, int test_min, int test_max, unsigned test_count): seed(seed), test_min(test_min),test_max(test_max), test_count(test_count) { }

    float operator()(GeneralState const &s) const {
        std::default_random_engine rng(seed);
        std::uniform_int_distribution<int> dstr(test_min,test_max);
        unsigned good = 0;
        for (unsigned cnt = 0; cnt != test_count; ++cnt)
            if (s.contains(dstr(rng))) ++good;

        return static_cast<float>(good)/static_cast<float>(test_count);
    }
};

int main(int argc, const char * argv[]) {
    DiscreteState d(1);
    SegmentState s(0,10);
    std::set<int> setN1 {2,5,6};
    Segment_and_delete_discrete_state asdfa1 (0,10, setN1);
    SegmentAndDots asdfa2 (10,20, setN1);
    SetState ss({1, 3, 5, 7, 23, 48, 57, 60, 90, 99});
    ProbabilityTest pt(10,0,100,100000);
    std::cout << pt(d) << std::endl;
    std::cout << pt(s) << std::endl;
    std::cout << pt(ss) << std::endl;
    std::cout << pt(asdfa1) << std::endl;
    std::cout << pt(asdfa2) << std::endl;
    return 0;
}
