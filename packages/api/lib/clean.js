const fs = require('fs')
const path = require('path')
const json = require('../data/livsmedelsdata.json')
const { seasons } = require('./seasonal')
const { convertNutritionalFacts } = require('./nutrition')

const data = json.LivsmedelDataset.LivsmedelsLista.Livsmedel

const categories = ['Grönsaker', 'Frukt färsk fryst']
const unwanted = [
  'förvälld',
  'konserv',
  'fryst',
  'kokt',
  'fruktsallad',
  'u skal',
  'u lag',
  'u dressing',
  'avrunna',
  'syltade',
  'citronskal',
  'inlagd',
  'stekt',
  'fräst',
]

const convertMainGroup = group => {
  switch (group) {
    case categories[0]:
      return 'vegetable'
    case categories[1]:
      return 'fruit'
    default:
      throw new Error('Unknown')
  }
}

const getSeasons = name => {
  return Object.keys(seasons)
    .map(key => {
      if (seasons[key].includes(name)) {
        return key
      }

      return false
    })
    .filter(Boolean)
}

const parseApple = name => {
  switch (name) {
    case 'Äpple rött typ röd aroma':
      return 'Äpple (röd aroma)'
    case 'Äpple rött typ Ingrid Marie':
      return 'Äpple (Ingrid Marie)'
    case 'Äpple typ Frida':
      return 'Äpple (Frida)'
    case 'Äpple grönt typ Golden delicious Granny Smith':
      return 'Äpple (Granny Smith)'
    case 'Persika nektarin':
      return 'Persika'
    case 'Småtomater röda typ körsbärstomat':
      return 'Körsbärstomat'
    case 'Småcitrus clementiner mandariner tangeriner satsumas':
      return 'Clementin'
    case 'Sparris grön el vit':
      return 'Sparris'
    default:
      return name
  }
}

const cleanName = name => {
  return parseApple(
    name
      .replace('fryst', '')
      .replace('kokt', '')
      .replace('färsk', '')
      .replace('m skal', '')
      .trim()
  )
}

const output = data
  .filter(item => categories.includes(item.Huvudgrupp))
  .filter(item => !unwanted.some(u => item.Namn.toLowerCase().includes(u)))
  .map(item => ({
    name: cleanName(item.Namn),
    category: convertMainGroup(item.Huvudgrupp),
    season: getSeasons(cleanName(item.Namn)),
    ...convertNutritionalFacts(item.Naringsvarden.Naringsvarde),
  }))

const asSql = output
  .map(
    item =>
      `INSERT INTO crop (${Object.keys(item).join(
        ', '
      )}) VALUES (${Object.values(item)
        .map(v => {
          if (Array.isArray(v)) {
            return `'{${v.map(v => `"${v}"`).join(',')}}'`
          }

          return `'${v}'`
        })
        .join(',')});`
  )
  .join('\n')

//console.log('after', JSON.stringify(output, null, 2))

fs.writeFileSync(
  path.resolve(__dirname, '../sql/insertData.sql'),
  asSql,
  'utf-8'
)
