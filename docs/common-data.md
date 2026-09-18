# Common data from games

The suite never reads a cart layout. Each `GameAdapter` turns save bytes and live RAM into one `GameSnapshot`. Static tables (`TrackerAtlas`, `CalcPack`, dex, names) are keyed by catalog UUID, difficulty, and patch option. Hacks still identify as their baseline cart.

Suite-owned files (`tracker.ini`, cheats, rules, host playtime) are not listed here.

## Save file

Needed from `battery.sav` for home plates, `Import from Existing .sav`, boxed mons, and any live path that does not map PC or flags.

**Trainer**

- name
- gender
- trainer id (TID + SID)
- in-game play clock (hours, minutes, seconds)

**Party (up to 6)**

- count
- each mon: the Mon blob below, including the party tail (level, current HP, max HP, Atk/Def/Spe/SpA/SpD, status)

**PC**

- current box index
- per box: name, 30 stored mons (Mon blob without party tail is enough; level comes from exp + growth)

**Overworld**

- map group, map number (name is looked up from static map tables)

**Progress**

- badge byte or badge flags (8 gyms)
- full flag bank (288 bytes) so tracker defeat flags and gym flags resolve
- CFRU expanded flags + vars when the title stores difficulty there (Radical Red flags, Unbound difficulty var, file signature)
- starter species (first party/box mon on the title's starter line; Hoenn internal ids map down to national)

Home plates also need party sprites and gym pips from this snapshot. Deaths come from `tracker.ini`, not the save.

## Live RAM

Needed while a run is seated. Live should refill the save-shaped snapshot when those blocks are mapped in EWRAM. Fields that save cannot keep current:

**Party (current)**

- same Mon blob as save, with live HP, max HP, stats, status, and level
- party count and slot order

**Overworld (current)**

- map group, map number, display name

**Progress (current)**

- flag bank and gym byte (FRLG auto-fill, RSE live)
- CFRU expanded flags/vars for in-game difficulty before the next save

**Battle (trainer battles only; zero if the title has no calc pack)**

- in battle
- weather (sun / rain / sand / hail)
- trainer table id when the game exposes it (calc prefers this; else match enemy species + levels)
- player battler: species, HP, max HP, 8 stages, status, party index
- foe battler: same
- enemy party: count, per slot species, level, current HP, max HP

CFRU live battle structs stay zero. Party HP still comes from the party snapshot.

Gen 4/5 live fills party and the trainer-battle overlay (HP, stages, enemy party). Boxes, flags, gyms, and map still come from the save merge.

## Mon blob (save or RAM)

Raw fields the snapshot stores per Pokemon:

- species id (game-internal; adapter or atlas maps to national)
- personality (PID; tracker identity, shiny, nature, gender)
- OT id, OT name
- nickname, species display name
- held item id
- experience
- ability number (gen 3: slot 0/1; gen 4/5: ability id)
- IVs: HP Atk Def Spe SpA SpD
- EVs: same six
- four moves + PP
- egg flag
- met location (catch-key match), met level, met game, ball

Derived, not stored as cart facts: nature (`pid % 25`), shiny (TID/SID/PID), gender (pid low byte vs species ratio), Showdown ability name, BST, level-from-exp when the party tail is missing.

Not needed: friendship, pokerus, language, ribbons, contest, pokerus days, markings.

## Static game data

Not per-save. Shipped with the suite, version-matched to the catalog title. A title is represented only when the atlas exists. Calculator stays empty until a pack exists.

**Species / dex (per damage generation, not cartridge generation)**

- national id, sprite slug, display name (`GameAdapter::species` or national fallback)
- types, base stats, two abilities, gender ratio, growth group, weight
- BST for box/grave sort
- vanilla names for the Pokémon tab
- starter-line roots (Bulbasaur line through gen 9) for rival locks and starter detect
- Hoenn internal id → national (`id - 25` in 277..411)

**Moves, items, abilities, natures**

- move id → name, type, base power, priority, kind (status / multi / OHKO / …), hits, contact, physical/special split when the chart needs it
- item id → name (separate gen 3 vs gen 4/5 tables)
- ability id → name
- nature id → name and stat multipliers

**Type chart + calc rules**

- `dmgGen`, `typeChart`, `switchIn` on the pack (CFRU is not gen 3)
- type effectiveness tables those ids select

**Map names**

- `(mapGroup, mapNum)` → Logs string (FRLG today)

**Tracker atlas (per catalog UUID × difficulty × patch option)**

- atlas id and starter species ids
- ordered stops:
  - id, kind (encounter / boss), name, locale
  - encounter: catch kind (starter / met), met-location ids
  - boss: kind (gym / rival / elite four / evil team / mini-boss), team slugs with optional starter lock, gym index 1..8, defeat flag + span
  - chrome: field count, tag, weather slug, note

Tracker auto-fill uses save/live flags, gym bits, starter, and every non-egg mon's species + PID + met location. Boss sprites come from the atlas team, not from RAM.

**Calc pack (per catalog UUID × variant)**

- every trainer: table id, name, class, location, AI flags, mandatory (leaders / E4 / champion / rival)
- each trainer mon: species, level, IV, item, four moves (learnset fill when the party has none), ability id when not species slot 0
- location index: name → trainer ids

Search is trainer and location, not species-first SETDEX.

**Sprites / title art**

- slug → box / front / back (cache, not git)
- catalog slug → 256×192 title plate

## Not from games

Wild encounter tables, bag, money, Pokedex seen/owned, daycare, mail. Tracker records catches from mons you actually have, keyed by met location, not from the wild table.
