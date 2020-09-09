# SMART HOME MANAGEMENT PLATFORM

## Summary
SmartHome is a next generation platform for managing IoT enhanced smart buildings.
The platform serves as the controller and integration hub for controllers and sensors that will enable efficient and comfortable operation of the building.
SmartHome is implemented using C++ for a POSIX compliant system.

## Main Components
The system includes the following components:
* A central hub, which is a server application serving as a host for software agents (below). It provides an efficient mechanism to receive events from sensors and dispatch these events to relevant controllers.
* Software agents, mediating communication with the external hardware devices. These devices can act either as sensors - monitoring and measuring a physical phenomena - or as controllers - executing an operation, usually affecting the environment.

Sensor agents generate events which will be routed to the controller agents interested in acting upon them.
Generated events contain at least: the event type, the event location, a timestamp and a data payload.
