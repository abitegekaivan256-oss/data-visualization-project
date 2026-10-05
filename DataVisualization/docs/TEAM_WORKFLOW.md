# Team Workflow

## Branch ownership
- Jackson: `jackson-data-loading`
- Gladys: `gladys-preprocessing`
- Adrian: `adrian-scatter`
- Sandra: `sandra-line`
- Jeff: `jeff-bar`
- Bonius: `bonius-axis-scaling`
- Ivan: `ivan-labels`

## Pull-request rule
No feature branch should be merged into `main` until it has been tested and reviewed by at least one other member.

## Before starting work each day
```bash
git checkout main
git pull origin main
git checkout <your-branch>
git merge main
```

## After work
```bash
git add .
git commit -m "Describe the change clearly"
git push
```

## Conflict prevention
1. Avoid editing another member's `.cpp` file unless agreed.
2. Discuss changes to shared files (`Plot`, `Renderer`, `main.cpp`) first.
3. Pull current `main` before integration.
4. Use Pull Requests rather than pushing feature work directly to `main`.
