const convertNutritionName = {
  'Summa mättade fettsyror': 'fat_saturated',
  'Summa enkelomättade fettsyror': 'fat_monounsaturated',
  'Summa fleromättade fettsyror': 'fat_polyunsaturated',
  'Fettsyra 4:0-10:0': 'fatty_acid',
  'Laurinsyra C12:0': 'lauric_acid',
  'Myristinsyra C14:0': 'myristic_acid',
  'Palmitinsyra C16:0': 'palmitic_acid',
  'Stearinsyra C18:0': 'stearic_acid',
  'Arakidinsyra C20:0': 'arachidic_acid',
  'Palmitoljesyra C16:1': 'palm_oil',
  'Oljesyra C18:1': 'oleic_acid',
  'Linolsyra C18:2': 'linoleic_acid',
  'Linolensyra C18:3': 'linolenic_acid',
  'Arakidonsyra C20:4': 'arachidonic_acid',
  'EPA (C20:5)': 'omega_3',
  'DPA (C22:5)': 'omega_3',
  'DHA (C22:6)': 'omega_3',
  Kolesterol: 'cholesterol',
  'Energi (kcal)': 'energy_kcal',
  'Socker totalt': 'sugar',
  Aska: 'ash',
  Vatten: 'water',
  Kolhydrater: 'carbohydrates',
  Protein: 'protein',
  Alkohol: 'alcohol',
  Fibrer: 'fiber',
  Fett: 'fat',
  Fosfor: 'phosphorus',
  Jod: 'iodine',
  Järn: 'iron',
  Kalcium: 'calcium',
  Kalium: 'potassium',
  Magnesium: 'magnesium',
  Selen: 'selenium',
  Zink: 'zinc',
  'Vitamin A': 'vitamin_a',
  Retinol: 'vitamin_a1',
  Tiamin: 'vitamin_b',
  Riboflavin: 'vitamin_b2',
  Niacin: 'vitamin_b3',
  'Vitamin B6': 'vitamin_b6',
  Folat: 'vitamin_b9',
  'Vitamin B12': 'vitamin_b12',
  'Vitamin C': 'vitamin_c',
  'Vitamin D': 'vitamin_d',
  'Vitamin E': 'vitamin_e',
  'β-Karoten': 'beta_carotene',
  'Fullkorn totalt': 'whole_grain',
  Salt: 'sodium',
}

const importantNutrition = [
  'energy_kcal',
  'carbohydrates',
  'sugar',
  'protein',
  'fat',
  'fat_saturated',
  'fat_monounsaturated',
  'fat_polyunsaturated',
  'fiber',
  'whole_grain',
  'iron',
  'sodium',
  'vitamin_a',
  'vitamin_a1',
  'vitamin_b',
  'vitamin_b2',
  'vitamin_b3',
  'vitamin_b6',
  'vitamin_b9',
  'vitamin_b12',
  'vitamin_c',
  'vitamin_d',
  'vitamin_e',
]

const convertNutritionalFacts = nutritional => {
  return nutritional
    .map(n => {
      return Object.keys(n).reduce((acc, key) => {
        if (key !== 'Varde') {
          return acc
        }

        const convertedName = convertNutritionName[n.Namn]

        if (!importantNutrition.includes(convertedName)) {
          return acc
        }

        return {
          ...acc,
          [convertedName]: parseFloat(n[key].replace(',', '.')),
        }
      }, {})
    })
    .reduce(
      (acc, curr) => ({
        ...acc,
        ...curr,
      }),
      {}
    )
}

module.exports = {
  convertNutritionalFacts,
}
