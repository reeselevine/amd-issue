#include <vector>
#include <iostream>
#include <easyvk.h>
#include <cassert>
#include <vector>
#include <unistd.h>

int main(int argc, char *argv[])
{
  int workgroupSize = 1;
  int numWorkgroups = 1;
  int deviceID = 0;
  bool enableValidationLayers = false;
  bool checkResults = false;
  int c;

  while ((c = getopt(argc, argv, "vd:")) != -1)
    switch (c)
    {
    case 'v':
      enableValidationLayers = true;
      break;
    case 'd':
      deviceID = atoi(optarg);
      break;
    case '?':
      if (optopt == 'd')
        std::cerr << "Option -" << optopt << "requires an argument\n";
      else
        std::cerr << "Unknown option" << optopt << "\n";
      return 1;
    default:
      abort();
    }

  auto bufferSize = 1024;
  // Initialize instance.
  auto instance = easyvk::Instance(enableValidationLayers);
  // Get list of available physical devices.
  auto physicalDevices = instance.physicalDevices();
  // Create device from first physical device.
  auto device = easyvk::Device(instance, physicalDevices.at(deviceID));
  std::cout << "Using device: " << device.properties.deviceName << "\n";

  // Define the buffers to use in the kernel.
  auto buf = easyvk::Buffer(device, bufferSize, sizeof(uint32_t));

  // Write initial values to the buffers.
  for (int i = 0; i < bufferSize; i++)
  {
    buf.store<uint32_t>(i, 1);
  }
  std::vector<easyvk::Buffer> bufs = {buf};

  const char* spvCode = "kernel.spv";

  auto program = easyvk::Program(device, spvCode, bufs);

  program.setWorkgroups(1);
  program.setWorkgroupSize(1);

  // Run the kernel.
  program.initialize("main");

  program.run();

  std::cout << "buf[2]: " << buf.load<uint>(2) << "\n";

  // Cleanup.
  program.teardown();
  buf.teardown();
  device.teardown();
  instance.teardown();
  return 0;
}
