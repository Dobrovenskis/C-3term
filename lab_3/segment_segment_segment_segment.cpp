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

class SegmentState: public GeneralState {
private:
    int const beg, end;

public:
    SegmentState(): SegmentState(0, -1) { }//beg(0), end(-1) { }
    SegmentState(int beg, int end): beg(beg), end(end) { }

    bool contains(int s) const {
        return s >= beg && s <= end;
    }
};

class SetState: public GeneralState {
private:
    std::set<int> const states;

public:
    SetState(): states() { }
    SetState(std::set<int> const &src): states(src) { }

    bool contains(int s) const {
        return states.count(s) > 0;
    }
};

class SuperState: public GeneralState
{
private:
    std::vector<DiscreteState> vec_discrete;
    std::vector<SegmentState> vec_segment;
    std::vector<DiscreteState> vec_delete_discrete;

public:
    SuperState(): vec_discrete(), vec_segment(), vec_delete_discrete() {}
    SuperState(std::vector<DiscreteState> &discrete, std::vector<SegmentState> &segment, std::vector<DiscreteState> &delete_discrete): vec_discrete(discrete), vec_segment(segment), vec_delete_discrete(delete_discrete) {}

    bool contains(int s) const {
        bool ret = false;

        for(DiscreteState el_discrete : vec_discrete)
        {
            if (el_discrete.contains(s))
            {
                ret = true;
            }
        }

        for(SegmentState el_segment : vec_segment)
        {
            if (el_segment.contains(s))
            {
                ret = true;
            }
        }

        for(DiscreteState el_segment : vec_delete_discrete)
        {
            if (el_segment.contains(s))
            {
                ret = false;
            }
        }
        return ret;
    }
};

class Set_segment_and_delete_discrete_state:public SuperState
{
private:
    //std::vector<SegmentState> vec_segment;
    //std::vector<DiscreteState> vec_delete_discrete;

public:
    Set_segment_and_delete_discrete_state(): SuperState() {}
    std::vector<DiscreteState> empty_discrete = std::vector<DiscreteState>();
    Set_segment_and_delete_discrete_state(std::vector<SegmentState> vec_seg, std::vector<DiscreteState> vec_disc): SuperState(empty_discrete,vec_seg, vec_disc) {}

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
    SetState ss({1, 3, 5, 7, 23, 48, 57, 60, 90, 99});
    ProbabilityTest pt(10,0,100,100000);
    std::cout << pt(d) << std::endl;
    std::cout << pt(s) << std::endl;
    std::cout << pt(ss) << std::endl;
    return 0;
}
