# Cub3d

Compilation : Make

Make val				->	compile avec valgrind et la map du sujet
Make val MAP=/map_path	->	change temporairement la map par defaut
OPTI=1					->	Optimisation graphique -O3

---

## Fonctions Raycasting

### raycasting.c
| Fonction | Rôle |
|---|---|
| `tex_pixel(tex, x, y)` | Retourne la couleur d'un pixel dans une texture (avec clamp) |
| `put_pixel(img, x, y, color)` | Ecrit un pixel dans une image mlx (avec bounds check) |
| `choose_texture(ctrl, ray)` | Retourne la bonne texture selon le côté touché (NO/SO/EA/WE) |
| `draw_floor_and_ceiling(ctrl)` | Copie le fond précompilé `F_C` dans `to_print` via `ft_memcpy` |
| `render_frame(ctrl)` | Lance `draw_floor_and_ceiling` puis `cast_rays` |

### raycasting2.c
| Fonction | Rôle |
|---|---|
| `init_dda_steps(ray, posX, posY)` | Calcule `step_x/y` et `side_dist_x/y` initiaux selon la direction du rayon |
| `perform_dda(ctrl, ray, posX, posY)` | Avance le rayon case par case jusqu'à un mur `'1'` |
| `compute_wall_projection(ray, wall, pos)` | Calcule la distance perp, `line_height`, `draw_start/end`, `wall_x` |
| `init_ray(ctrl, ray, posX, posY, cameraX)` | Initialise `ray_dir`, `map_x/y`, `delta_dist` pour une colonne |
| `cast_rays(ctrl)` | Boucle sur chaque colonne de l'écran et appelle les 3 étapes ci-dessus |

### raycasting3.c
| Fonction | Rôle |
|---|---|
| `init_tex_coords(wall, tex, ray)` | Calcule `tex_x` (avec flip), `step` et `tex_pos` de départ |
| `draw_column(ctrl, tex, x, wall, ray)` | Dessine la colonne de mur pixel par pixel avec la texture |
| `draw_wall_stripe(ctrl, x, ray, wall)` | Point d'entrée : choisit la texture, appelle les deux fonctions ci-dessus |

