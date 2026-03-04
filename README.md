C++ Code samples for EXO, my Unreal Engine 5 Capstone project.

https://malachek.com/exo

**EnemyManager.cpp/.h** (Memory Management & Object Pooling):
> Implemented robust Object Pool pattern using a custom Intrusive Linked List to eliminate runtime allocation, garbage collection overhead, and maintain proper memory managemnet. Dynamically expands pool size when exhausted to maintain framerate during high enemy density.

**ExoEnemyBase.cpp/.h** (Lifecycle Management & Optimization):
> Designed specifically for object pooling integration. Handles rapid activation and deactivation by stripping and resetting physics, collisions, visibility, and AI states without the heavy engine cost of standard actor spawning/destroying.

**ExoCharacterBase.cpp/.h** (System Integration & Network Replication):
> Foundation character class implementing Unreal's Gameplay Ability System (GAS) via IAbilitySystemInterface. Configures the Ability System Component with Mixed replication handling, ensuring a scalable multiplayer-ready architecture.

**BasicAttributeSet.cpp/.h** (Data Management & Gameplay Logic):
> GAS attribute definitions for core combat stats. Utilizes engine-level modifier callbacks (PreAttributeChange, PostGameplayEffectExecute) to safely clamp and strictly enforce rules on variables like Health and Soul before effects are applied.
