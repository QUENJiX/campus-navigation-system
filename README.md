# Campus Navigation System — CSE225L

A simple C++ campus navigation project for CSE225L, grounded in the data structures taught in the lab manuals.

## What is in this repository

- `src/` — Code::Blocks/C++ project source
- `index.html`, `style.css`, `script.js` — the team + viva handbook site
- `assets/nsu-map.png` — the original custom campus map used to design the graph
- `assets/campus-graph.svg` — simplified final graph visualization

The handbook is meant to be our working source of truth for the map, graph connections, architecture, lab grounding, member division, features, algorithms, viva variations, testing, demo, and future updates.

## Core project requirements

- adjacency-list graph
- BFS
- DFS
- shortest path in an unweighted graph
- dynamic addition and removal of roads

## GitHub Pages

Once Pages is enabled for this repository from `main` / root, the handbook will be available at:

`https://quenjix.github.io/campus-navigation-system/`


## Local preview

You can open `index.html` directly in a browser. For a local web server, run this from the repository folder:

```bash
python -m http.server 8000
```

Then open `http://localhost:8000`.

## Source-of-truth rule

If the graph, code, member responsibilities, or viva plan changes, update the website in the same commit. The final vertex/edge tables on the site override older sketches.

## Handbook navigation

The handbook sidebar is collapsible. All navigation groups start closed, and the group containing the section currently being read opens automatically as you scroll. The graph visualization is an exact topology diagram of the 18 vertices and 19 undirected edges used by the code.
