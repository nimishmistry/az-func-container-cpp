# Containerized Azure Function App with C++

This sample demonstrates creation of an Azure Function App running in Linux containers.

This sample has been created with c++, oat++ and docker on linux

# Build

## Building the service


### Oat++
The service uses a third party library Oat++

https://oatpp.io/

Oat++ references are managed with vcpkg.

### Vcpkg

vcpkg setup instructions are available on it's homepage

https://vcpkg.io/en/getting-started.html


Once vcpkg is setup, you need to set an environment variable to the path of vcpkg root

```
export VCPKG_ROOT=<vcpkg_root>
```

### CMake

The service is built with cmake

#### Configuration

```
cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_COMPILER=g++ -DCMAKE_TOOLCHAIN_FILE=$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake -S ./service -B ./.build -G Ninja

```

#### Build
cmake --build ./.build

### Docker Image

Once the service is built, you need to create a docker image

```shell
# Set environment variables for location and resource group

# Azure region
export LOCATION=<location>

# Name for the resource group
export RESOURCE_GROUP=<resource-group>

# Credentials for the container registry
export CONTAINER_REGISTRY_URL=<url>
export CONTAINER_REGISTRY_USERNAME=<username>
export CONTAINER_REGISTRY_PASSWORD=<password>

# Name of the docker image
export CONTAINER_IMAGE=<image_name>

docker login --username $CONTAINER_REGISTRY_USERNAME --password $CONTAINER_REGISTRY_PASSWORD $CONTAINER_REGISTRY_URL

docker build -t $CONTAINER_REGISTRY_URL/$CONTAINER_IMAGE ./.build

docker push -t $CONTAINER_REGISTRY_URL/$CONTAINER_IMAGE
```

### Deploy Function to Azure

Start an Azure cloud shell

Copy the configuration folder to the cloud drive and execute the following commands

```shell
# Create resource group
az group create --location $LOCATION --name $RESOURCE_GROUP

# Deploy the bicep
az deployment group create --resource-group $RESOURCE_GROUP --template-file ./configuration/function.bicep --parameters appName=cpp-az-func-test-app containerImageUrl=$CONTAINER_REGISTRY_URL/$CONTAINER_IMAGE containerRegistryUrl=$CONTAINER_REGISTRY_URL containerRegistryUsername=$CONTAINER_REGISTRY_USERNAME containerRegistryPassword=$CONTAINER_REGISTRY_PASSWORD

###
```