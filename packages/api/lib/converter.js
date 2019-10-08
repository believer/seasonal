const parser = require('xml2json')
const fs = require('fs')

const xml = fs.readFileSync('../data/livsmedelsdata.xml', 'utf-8')

const json = JSON.parse(parser.toJson(xml))
const output = JSON.stringify(data, '', '  ')

fs.writeFileSync('../data/livsmedelsdata.json', output, 'utf-8')
