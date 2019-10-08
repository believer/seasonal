\connect postgres;

----------------------------------------------------------
-- Create database
----------------------------------------------------------
drop database if exists seasonal;
create database seasonal;
\connect seasonal;

----------------------------------------------------------
-- Create crop
----------------------------------------------------------
create type crop_category as enum (
  'fruit',
  'vegetable'
);

create type season_month as enum (
  'jan',
  'feb',
  'mar',
  'apr',
  'may',
  'jun',
  'jul',
  'aug',
  'sep',
  'oct',
  'nov',
  'dec'
);

create table crop (
  id serial primary key,
  name text unique not null,
  category crop_category not null,
  season season_month[],
  energy_kcal integer not null default 0,
  carbohydrates float not null default 0.0,
  sugar float not null default 0.0,
  protein float not null default 0.0,
  fat float not null default 0.0,
  fat_saturated float not null default 0.0,
  fat_monounsaturated float not null default 0.0,
  fat_polyunsaturated float not null default 0.0,
  fiber float not null default 0.0,
  whole_grain float not null default 0.0,
  vitamin_a float not null default 0.0,
  vitamin_a1 float not null default 0.0,
  vitamin_b float not null default 0.0,
  vitamin_b2 float not null default 0.0,
  vitamin_b3 float not null default 0.0,
  vitamin_b6 float not null default 0.0,
  vitamin_b9 float not null default 0.0,
  vitamin_b12 float not null default 0.0,
  vitamin_c float not null default 0.0,
  vitamin_d float not null default 0.0,
  vitamin_e float not null default 0.0,
  iron float not null default 0.0,
  sodium float not null default 0.0
);

-- Create energy_kj based on energy_kcal
create function crop_energy_kj(crop crop) returns integer as $$
  select round(crop.energy_kcal * 4.184)::integer;
$$ language sql stable;

comment on function crop_energy_kj(crop) is 'The energy in kJ calculated from energy kcal';

-- Add descriptions
comment on table crop is 'A crop';
comment on column crop.id is 'The primary identifier of a crop';
comment on column crop.name is 'The name of the crop';
comment on column crop.category is 'The crops category';
comment on column crop.energy_kcal is 'The crops energy content (kcal)';
comment on column crop.carbohydrates is 'The crops carbohydrates (g)';
comment on column crop.sugar is 'The crops sugar (g)';
comment on column crop.fat is 'The crops fat (g)';
comment on column crop.fat_saturated is 'The crops saturated fat content (g)';
comment on column crop.fat_monounsaturated is 'The crops monounsaturated fat content (g)';
comment on column crop.fat_polyunsaturated is 'The crops polyunsaturated fat content (g)';
comment on column crop.protein is 'The crops protein (g)';
comment on column crop.fibers is 'The crops fibers (g)';
comment on column crop.whole_grain is 'The crops whole grain (g)';
comment on column crop.vitamin_d is 'The crops vitamin D content (µg)';
comment on column crop.vitamin_c is 'The crops vitamin C content (mg)';
comment on column crop.vitamin_b9 is 'The crops vitamin B9 content (µg)';
comment on column crop.iron is 'The crops iron content (mg)';
comment on column crop.sodium is 'The crops sodium content (g)';
