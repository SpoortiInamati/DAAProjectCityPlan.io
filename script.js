// ---------------- MODULE DATA (each module: 10 ideas + algos) ----------------
const MODULES = {
  port: {
    title: "Port Nervous System",
    desc: "Optimizes vessel scheduling, berth allocation and cargo flow for Tarangapur port.",
    ideas: [
      {t:"Automated berth scheduling", d:"Dynamic berth assignment to minimize turnaround."},
      {t:"Smart crane dispatch", d:"Prioritize cranes using job queues & heuristics."},
      {t:"Predictive ETA for vessels", d:"ML model to forecast arrival times."},
      {t:"Cargo routing optimizer", d:"Graph shortest-path for container movement."},
      {t:"Energy-aware port ops", d:"Reduce peak load using scheduling."},
      {t:"Autonomous docking assistant", d:"Vision + control loop for docking."},
      {t:"Customs automated screening", d:"Anomaly detection for security."},
      {t:"Harbor pollution tracker", d:"Sensor fusion + time series alerts."},
      {t:"Demand-based labor roster", d:"Optimization + forecasting."},
      {t:"Digital twin simulation", d:"Simulate port scenarios for planning."}
    ],
    algos: ["Dijkstra / A* for routing","Time-series forecasting (LSTM)","Genetic Algorithms for scheduling","Greedy heuristics","Anomaly detection"]
  },

  energy: {
    title: "Offshore Energy Grid",
    desc: "Orchestrates wind, wave and solar resources with demand forecasting.",
    ideas: [
      {t:"Wave-to-grid scheduling", d:"Match wave power curves to demands."},
      {t:"Predictive maintenance", d:"Sensor anomaly + remaining-life models."},
      {t:"Energy trading optimizer", d:"Market-aware balancing algorithm."},
      {t:"Microgrid islanding", d:"Seamless transition to local islands."},
      {t:"Battery dispatch", d:"Min-cost dispatch with constraints."},
      {t:"Offshore drone inspection", d:"Autonomous scheduling & routing."},
      {t:"Load forecasting", d:"Short-term energy forecasts."},
      {t:"Tidal pattern analyzer", d:"Signal processing + ML."},
      {t:"Hybrid resource scheduler", d:"Integer programming for allocation."},
      {t:"Demand response platform", d:"Reinforcement learning for incentives."}
    ],
    algos: ["Time-series models","Integer Programming","Reinforcement Learning","Genetic Algorithms","Kalman Filters"]
  },

  traffic: {
    title: "Traffic Flow AI",
    desc: "Optimizes intersections, predicts congestion, and suggests routing.",
    ideas: [
      {t:"Adaptive signal control", d:"Change lights with real-time flows."},
      {t:"Priority lanes for emergency", d:"Dynamic activation & route clearing."},
      {t:"Predictive congestion alerts", d:"Short-term flow forecasting."},
      {t:"Multi-modal planner", d:"Integrate buses, ferries and bikes."},
      {t:"Parking availability predictor", d:"Guidance to empty slots."},
      {t:"EV charging scheduler", d:"Coordinate charging times."},
      {t:"Freight corridor optimization", d:"Separate cargo flows."},
      {t:"Crowd-aware routing", d:"Avoid dense pedestrian zones."},
      {t:"Green-wave planner", d:"Coordinate lights for less stops."},
      {t:"Simulation sandbox", d:"What-if scenarios for policy."}
    ],
    algos: ["Reinforcement Learning","Queuing Theory","Graph Shortest Path","Time-series Forecasting","Simulations"]
  },

  water: {
    title: "Water & Desalination Ops",
    desc: "Smart allocation, leak detection and efficient desalination.",
    ideas: [
      {t:"Pressure-based leak detection", d:"Anomaly detection across sensor network."},
      {t:"Demand-aware distribution", d:"Optimize pumps to reduce cost."},
      {t:"Desalination optimization", d:"Thermodynamic + scheduling improvements."},
      {t:"Brine disposal plan", d:"Minimize environmental impact."},
      {t:"Smart meters with incentives", d:"Encourage off-peak usage."},
      {t:"Rainwater harvesting scheduler", d:"Local storage management."},
      {t:"Quality monitoring", d:"Real-time sensor QA."},
      {t:"Cross-network routing", d:"Reroute during failures."},
      {t:"Predictive maintenance for pumps", d:"Failure prediction models."},
      {t:"Water reuse loops", d:"Greywater circular systems."}
    ],
    algos: ["Anomaly detection","Linear programming","Time-series models","Sensor fusion","Control theory"]
  },

  safety: {
    title: "Safety & Response",
    desc: "Alerting, routing and dispatch for emergencies with predictive monitoring.",
    ideas: [
      {t:"Smart dispatch", d:"Assign nearest resources using graph search."},
      {t:"Crowd-sourced incident reporting", d:"Prioritize via confidence scoring."},
      {t:"Predictive hotspot detection", d:"ML to find risky zones."},
      {t:"Route resilience planner", d:"Alternative routing under constraints."},
      {t:"Drone rapid assessment", d:"Autonomous scene triage."},
      {t:"Mass-notification engine", d:"Tiered alerts for citizens."},
      {t:"First-responder path optimizer", d:"Multi-agent coordination."},
      {t:"Resource prepositioning", d:"Stochastic optimization for placement."},
      {t:"Simulation drills", d:"Run virtual emergency scenarios."},
      {t:"Privacy-safe CCTV analytics", d:"Edge detection & aggregated alerts."}
    ],
    algos: ["Multi-agent pathfinding","Stochastic Optimization","Anomaly detection","Federated learning","Graph algorithms"]
  },

  tourism: {
    title: "Coastal Tourism Tech",
    desc: "Enhances tourist flow, safety and local business discovery.",
    ideas: [
      {t:"Dynamic tour recommendation", d:"Personalized itineraries."},
      {t:"Peak-time pricing for attractions", d:"Demand smoothing."},
      {t:"Smart signage & AR guides", d:"Augmented visitor experience."},
      {t:"Local marketplace platform", d:"Connect artisans & tourists."},
      {t:"Eco-tourism schedules", d:"Protect sensitive habitats."},
      {t:"Transport bundling", d:"Combine ferry + bus for trips."},
      {t:"Real-time beach safety", d:"Currents & lifeguard alerts."},
      {t:"Sustainability scoring", d:"Show business eco rank."},
      {t:"Visitor sentiment analysis", d:"Improve services."},
      {t:"Seasonal workforce planning", d:"Optimize hiring cycles."}
    ],
    algos: ["Recommendation systems","A/B testing","Forecasting","Optimization","NLP sentiment analysis"]
  }
};

// ---------------- DOM bindings ----------------
const explorer = document.getElementById('explorer');
const expTitle = document.getElementById('exp-title');
const expDesc = document.getElementById('exp-desc');
const ideasContainer = document.getElementById('ideas');
const algosList = document.getElementById('algos');

function openModule(key){
  if(!MODULES[key]) return;
  const m = MODULES[key];
  expTitle.textContent = m.title;
  expDesc.textContent = m.desc;

  ideasContainer.innerHTML = '';
  m.ideas.forEach(item=>{
    const el = document.createElement('div');
    el.className = 'idea';
    el.innerHTML = `<h4>${item.t}</h4><p>${item.d}</p>`;
    ideasContainer.appendChild(el);
  });

  algosList.innerHTML = '';
  m.algos.forEach(a=>{
    const li = document.createElement('li');
    li.textContent = a;
    algosList.appendChild(li);
  });

  explorer.classList.add('show');
  explorer.setAttribute('aria-hidden', 'false');
}

// close modal
document.getElementById('closeX').addEventListener('click', ()=>{
  explorer.classList.remove('show');
  explorer.setAttribute('aria-hidden', 'true');
});

// wire module cards
document.querySelectorAll('.module').forEach(btn=>{
  btn.addEventListener('click', ()=> openModule(btn.dataset.key));
  btn.addEventListener('keydown', (e)=>{ if(e.key === 'Enter') openModule(btn.dataset.key); });
});

// quick stats animation
setInterval(()=>{
  const energyEl = document.getElementById('energy');
  energyEl.innerText = (90 + Math.floor(Math.random()*8)) + "%";
  document.getElementById('port').innerText = Math.random()>0.12 ? 'ACTIVE' : 'DEGRADED';
  document.getElementById('ocean').innerText = Math.random()>0.08 ? 'SAFE' : 'WATCH';
}, 2200);

// small helper: mobile menu
function toggleMenu(){
  const nav = document.querySelector('.menu');
  if(!nav) return;
  nav.style.display = (nav.style.display === 'block') ? '' : 'block';
}

// animate AOS (if loaded)
if(window.AOS) AOS.init({duration:700, once:true});

// footer year
document.getElementById('year').textContent = new Date().getFullYear();
