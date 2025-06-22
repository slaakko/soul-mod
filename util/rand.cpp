// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module util.rand;

#ifdef OTAVA

extern "C" std::uint8_t get_random_byte();
extern "C" void set_rand_seed(std::uint64_t seed);

#endif

namespace util {

#ifdef OTAVA

std::uint8_t get_random_byte()
{
    return ::get_random_byte();
}

void set_rand_seed(std::uint64_t seed)
{
    ::set_rand_seed(seed);
}

#else

class Rng
{
public:
    Rng(std::uint64_t seed_);
    std::uint8_t Get() { return dist(mt); }
private:
    std::random_device rd;
    std::uint64_t seed;
    std::mt19937_64 mt;
    std::uniform_int_distribution<> dist;
};

std::uint64_t GetSeed(std::uint64_t seed, std::random_device& rd)
{
    if (seed == -1)
    {
        return static_cast<std::uint64_t>(rd()) ^ static_cast<std::uint64_t>(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    }
    else
    {
        return seed;
    }
}

Rng::Rng(std::uint64_t seed_) : rd(), seed(GetSeed(seed_, rd)), mt(seed), dist(0, 255)
{
}

#ifdef _WIN32

__declspec(thread) std::uint64_t init_seed = -1;
__declspec(thread) Rng* rng = nullptr;

#else

__thread std::uint64_t init_seed = -1;
__thread Rng* rng = nullptr;

#endif

void set_rand_seed(std::uint64_t seed)
{
    init_seed = seed;
}

void reset_rng()
{
    if (rng)
    {
        delete rng;
        rng = nullptr;
    }
}

std::uint8_t get_random_byte()
{
    if (!rng)
    {
        rng = new Rng(init_seed);
    }
    return rng->Get();
}

#endif

} // namespace util
