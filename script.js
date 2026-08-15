const sidebar = document.getElementById('sidebar');
const menu = document.getElementById('mobileMenu');
const backdrop = document.getElementById('sidebarBackdrop');
const backTop = document.getElementById('backTop');
const progress = document.getElementById('scrollProgress');
const navSearch = document.getElementById('navSearch');
const navLinks = [...document.querySelectorAll('.nav-link')];

function setMenu(open) {
  sidebar.classList.toggle('open', open);
  backdrop.classList.toggle('open', open);
  menu.setAttribute('aria-expanded', String(open));
}
menu.addEventListener('click', () => setMenu(!sidebar.classList.contains('open')));
backdrop.addEventListener('click', () => setMenu(false));
navLinks.forEach(link => link.addEventListener('click', () => setMenu(false)));

document.querySelectorAll('.nav-group-title').forEach(btn => {
  btn.addEventListener('click', () => {
    const group = btn.closest('.nav-group');
    const collapsed = group.classList.toggle('collapsed');
    btn.setAttribute('aria-expanded', String(!collapsed));
  });
});

navSearch.addEventListener('input', e => {
  const q = e.target.value.trim().toLowerCase();
  document.querySelectorAll('.nav-group').forEach(group => {
    let visible = 0;
    group.querySelectorAll('.nav-link').forEach(link => {
      const hit = !q || link.textContent.toLowerCase().includes(q);
      link.classList.toggle('hidden', !hit);
      if (hit) visible++;
    });
    group.style.display = visible ? '' : 'none';
    if (q && visible) group.classList.remove('collapsed');
  });
});

const observed = navLinks
  .map(link => document.getElementById(link.dataset.section))
  .filter(Boolean);
const linkById = new Map(navLinks.map(link => [link.dataset.section, link]));
const observer = new IntersectionObserver(entries => {
  const visible = entries.filter(e => e.isIntersecting).sort((a,b) => b.intersectionRatio - a.intersectionRatio);
  if (!visible.length) return;
  navLinks.forEach(l => l.classList.remove('active'));
  const active = linkById.get(visible[0].target.id);
  if (active) {
    active.classList.add('active');
    active.scrollIntoView({block: 'nearest'});
  }
}, { rootMargin: '-15% 0px -72% 0px', threshold: [0, .2, .6] });
observed.forEach(el => observer.observe(el));

function onScroll() {
  const max = document.documentElement.scrollHeight - window.innerHeight;
  const pct = max > 0 ? (window.scrollY / max) * 100 : 0;
  progress.style.width = pct + '%';
  backTop.classList.toggle('visible', window.scrollY > 700);
}
window.addEventListener('scroll', onScroll, {passive: true});
onScroll();
backTop.addEventListener('click', () => window.scrollTo({top: 0, behavior: 'smooth'}));
