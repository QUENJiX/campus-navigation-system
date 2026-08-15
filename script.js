const body = document.body;
const sidebar = document.getElementById('sidebar');
const menu = document.getElementById('mobileMenu');
const desktopToggle = document.getElementById('desktopSidebarToggle');
const backdrop = document.getElementById('sidebarBackdrop');
const backTop = document.getElementById('backTop');
const progress = document.getElementById('scrollProgress');
const navSearch = document.getElementById('navSearch');
const navLinks = [...document.querySelectorAll('.nav-link')];
const navGroups = [...document.querySelectorAll('.nav-group')];
const observed = navLinks.map(link => document.getElementById(link.dataset.section)).filter(Boolean);
const linkById = new Map(navLinks.map(link => [link.dataset.section, link]));
let searching = false;
let scrollTicking = false;

function setMobileMenu(open) {
  sidebar.classList.toggle('open', open);
  backdrop.classList.toggle('open', open);
  menu.setAttribute('aria-expanded', String(open));
}

function setDesktopSidebar(collapsed) {
  body.classList.toggle('sidebar-collapsed', collapsed);
  desktopToggle.textContent = collapsed ? '›' : '‹';
  desktopToggle.setAttribute('aria-label', collapsed ? 'Open navigation' : 'Collapse navigation');
  desktopToggle.setAttribute('title', collapsed ? 'Open navigation' : 'Collapse navigation');
  desktopToggle.setAttribute('aria-expanded', String(!collapsed));
}

function collapseGroup(group) {
  group.classList.add('collapsed');
  group.querySelector('.nav-group-title')?.setAttribute('aria-expanded', 'false');
}

function expandGroup(group) {
  group.classList.remove('collapsed');
  group.querySelector('.nav-group-title')?.setAttribute('aria-expanded', 'true');
}

function collapseAllGroups(except = null) {
  navGroups.forEach(group => {
    if (group === except) expandGroup(group);
    else collapseGroup(group);
  });
}

function clearActiveNavigation() {
  navLinks.forEach(link => link.classList.remove('active'));
  if (!searching) collapseAllGroups();
}

function activateSection(id) {
  const active = linkById.get(id);
  if (!active) {
    clearActiveNavigation();
    return;
  }

  navLinks.forEach(link => link.classList.toggle('active', link === active));

  if (!searching) {
    const group = active.closest('.nav-group');
    collapseAllGroups(group);
  }

  active.scrollIntoView({ block: 'nearest' });
}

function updateActiveSection() {
  if (!observed.length) return;

  const trigger = 150;
  const firstTop = observed[0].getBoundingClientRect().top;
  if (firstTop > trigger) {
    clearActiveNavigation();
    return;
  }

  let current = observed[0];
  for (const section of observed) {
    if (section.getBoundingClientRect().top <= trigger) current = section;
    else break;
  }
  activateSection(current.id);
}

menu.addEventListener('click', () => setMobileMenu(!sidebar.classList.contains('open')));
backdrop.addEventListener('click', () => setMobileMenu(false));
desktopToggle.addEventListener('click', () => setDesktopSidebar(!body.classList.contains('sidebar-collapsed')));

navLinks.forEach(link => link.addEventListener('click', () => {
  if (window.innerWidth <= 900) setMobileMenu(false);
  activateSection(link.dataset.section);
}));

document.querySelectorAll('.nav-group-title').forEach(button => {
  button.addEventListener('click', () => {
    const group = button.closest('.nav-group');
    const willOpen = group.classList.contains('collapsed');
    collapseAllGroups(willOpen ? group : null);
  });
});

navSearch.addEventListener('input', event => {
  const query = event.target.value.trim().toLowerCase();
  searching = Boolean(query);

  navGroups.forEach(group => {
    let visible = 0;
    group.querySelectorAll('.nav-link').forEach(link => {
      const hit = !query || link.textContent.toLowerCase().includes(query);
      link.classList.toggle('hidden', !hit);
      if (hit) visible++;
    });
    group.style.display = visible ? '' : 'none';
    if (query && visible) expandGroup(group);
  });

  if (!query) {
    navGroups.forEach(group => group.style.display = '');
    updateActiveSection();
  }
});

function onScroll() {
  const max = document.documentElement.scrollHeight - window.innerHeight;
  const pct = max > 0 ? (window.scrollY / max) * 100 : 0;
  progress.style.width = pct + '%';
  backTop.classList.toggle('visible', window.scrollY > 700);

  if (!scrollTicking) {
    window.requestAnimationFrame(() => {
      if (!searching) updateActiveSection();
      scrollTicking = false;
    });
    scrollTicking = true;
  }
}

window.addEventListener('scroll', onScroll, { passive: true });
window.addEventListener('resize', () => {
  if (window.innerWidth > 900) setMobileMenu(false);
  if (!searching) updateActiveSection();
});

backTop.addEventListener('click', () => window.scrollTo({ top: 0, behavior: 'smooth' }));

// Start with every group closed. Scrolling opens only the current group.
collapseAllGroups();
setDesktopSidebar(false);
onScroll();
