// cpp/include/Utils.hpp
#ifndef UTILS_HPP
#define UTILS_HPP

/**
 * \brief Class Utils: Singleton
 */
class Utils
{
public:
    static Utils &getInstance()
    {
        static Utils instance;
        return instance;
    }

    /**
     * Delete copy constructor and assignment operator
     * */
    Utils(const Utils &) = delete;
    void operator=(const Utils &) = delete;

    /**
     * \brief Combination of n in r: Heuristic to avoid large multiplications
     * \param n Int type: first element in combination
     * \param r Int type: second element in combination
     */
    long long nCr(int n, int r);

private:
    Utils() {}
};

#endif