J'ai repris tout l'asm pour y implementer l'utilisation du tableau de op.c et un
maximum de macros de op.h, comme ca on a un assembleur plus adaptable.

J'ai ajoute de la gestion d'erreur au fur et a mesure, tout passe par la
fonction exit_free, qui peut etre complexifiee selon la finesse des messages
d'erreur qu'on veut sortir.

La totalite n'est pas testable, puisque j'ai pas totalement fini get_param, et
qu'il me reste get_param_type a coder. Cette derniere devra faire les memes
verifications de format sur chaque parametre potentiel qui lui sera envoyé, puis
faire appelle a is_direct, is_index, et is_registre.

Il me manque donc aussi une version finale de ces trois fonctions la, avec un
parsing 100% safe.


A VOIR ENSEMBLE : les choix sur l'affichage des erreurs, et les cas particulier
auquels la version "finale" de mon parsing n'aura pas forcement en compte
