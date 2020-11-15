#include <boost/compute/core.hpp>
#include <iostream>

namespace compute = boost::compute;

int main()
{
    compute::device device = compute::system::default_device();

    std::cout << device.name() << " (platform: " << device.platform().name() << ")" << std::endl;

    return 0;
}

