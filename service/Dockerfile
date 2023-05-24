FROM ubuntu:latest

WORKDIR /app

# Copy swagger files
COPY ./external ./external

# Copy service binaries
COPY ./ExampleService .

# Expose port
EXPOSE 80

# Set execute permissions
RUN chmod +x ./ExampleService

# Start the service
CMD [ "./ExampleService" ]
