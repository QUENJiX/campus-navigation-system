# Campus Navigation System — CSE225L

A simple C++ campus navigation project for CSE225L, grounded in the data structures and graph algorithms taught in the lab manuals.

## What is in this repository

- `src/` — Code::Blocks/C++ project source
- `index.html`, `style.css`, `script.js` — the team + viva handbook site
- `assets/nsu-map.png` — the custom campus map used to design the graph
- `assets/campus-graph.svg` — exact current graph visualization

The handbook is the working source of truth for the map, graph connections, architecture, lab grounding, member division, features, algorithms, viva variations, testing, and demo plan.

## Core assignment requirements

- adjacency-list graph
- BFS traversal
- DFS traversal
- shortest path in an unweighted graph
- dynamic addition and removal of roads

## Additional implemented features

The project now also includes six lightweight graph-analysis features that reuse the same taught ADTs and algorithms:

- check whether two locations are directly connected
- show all direct neighbors of one location
- show the degree of a location
- show campus statistics: location count, road count, and most-connected location
- check whether one location is reachable from another using BFS
- find all locations within a user-selected number of hops using Queue + `distance[]`

Search by ID/name, formatted displays, and full shortest-route reconstruction are also included beyond the minimum assignment bullets.

## Current graph baseline

- 18 vertices
- 23 undirected edges
- unweighted, so every direct edge has conceptual cost 1
- Ground Floor is the current highest-degree vertex with degree 8

Important corrected connections include:

- Female Lounge `<->` Ground Floor
- Male Lounge `<->` Ground Floor
- Cafeteria `<->` Ground Floor, NAC, SAC, and Gate 8
- Central Library `<->` Upper Plaza, Gallery, and SAC

## Build

Open `src/CampusNavigationSystem.cbp` in Code::Blocks and build the project, or compile the project-specific source from a terminal with a C++11 compiler.

The program is designed for the Windows/Code::Blocks lab environment. Its menu clears the previous console screen before each action and pauses before returning to the menu so the output stays readable.

## GitHub Pages

Once Pages is enabled for this repository from `main` / root, the handbook will be available at:

`https://quenjix.github.io/campus-navigation-system/`

## Local website preview

You can open `index.html` directly in a browser. For a local web server, run this from the repository folder:

```bash
python -m http.server 8000
```

Then open `http://localhost:8000`.

## Source-of-truth rule

If the graph, code, member responsibilities, or viva plan changes, update the website in the same commit. The final vertex/edge tables on the site override older sketches.

## Handbook navigation

The handbook sidebar is collapsible. All navigation groups start closed, and the group containing the section currently being read opens automatically as you scroll. The graph visualization reflects the exact current topology of 18 vertices and 23 undirected edges.
