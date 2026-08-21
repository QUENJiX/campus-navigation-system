# Campus Navigation System

Source-code baseline: **simple v1.1-style version**. Viva/site refresh: **2026-08-21**. — CSE225L

A straightforward C++ campus navigation project using only the data structures and graph ideas taught in the course labs.

## Core project features

- adjacency-list graph using linked-list `UnsortedType<int>`
- BFS traversal using Queue
- DFS traversal using Stack
- shortest path in an unweighted graph using BFS
- dynamic addition and removal of roads
- display locations/connections
- search location by ID or name

The later extra-feature version (degree/statistics/reachability/N-hops, etc.) is **not** used in this package.

## Current graph

- 18 vertices
- 23 undirected roads
- unweighted: every direct connection has cost 1
- Ground Floor has the highest degree: 8

Important corrected connections include:

- Female Lounge `<->` Ground Floor
- Male Lounge `<->` Ground Floor
- Cafeteria `<->` Ground Floor, NAC, SAC, and Gate 8
- Central Library `<->` Upper Plaza, Gallery, and SAC

## Team ownership

- Member 1 — Hasib: map/topology, graph setup, `AddLocation()`, `ShortestPath()`
- Member 2 — Jaima: adjacency lists, `AddRoad()`, `RemoveRoad()`, validation
- Member 3 — Risha: BFS, Queue, marks, `GetToVertices()`
- Member 4 — Fabiha: menu/input, display, ID/name search
- Member 5 — Safwan: DFS and Stack integration

## Build

Open `src/CampusNavigationSystem.cbp` in Code::Blocks, or compile with a C++11 compiler.

## Handbook

Open `index.html`. The Viva Prep section shows only a few realistic modifications for each member, including exactly which function/file to change and roughly how much code changes.
