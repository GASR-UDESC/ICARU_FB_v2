

import ply.lex as lex

# List of token names.   This is always required
tokens = (
'TO',
'BI_SET_REG',
'BI_GET_REG',
'BI_GET_REG_REAL',
'ARROW',
'ASSIGNMENT',
'TWO_POINTS',
'SEMICOLON',
'OP',
'CP',
'COMA',
'POINT',
'HASH',
'OR',
'AND',
'NOT',
'XOR',
'GT',
'GE',
'LT',
'LE',
'EQ',
'ADD',
'SUB',
'MUL',
'DIV',
'AT',
'ALGORITHM',
'END_ALGORITHM',
'IN',
'EVENT_INPUT',
'EVENT_OUTPUT',
'END_EVENT',
'EC_STATES',
'END_STATES',
'EC_TRANSITIONS',
'END_TRANSITIONS',
'EVENT_CONNECTIONS',
'DATA_CONNECTIONS',
'END_CONNECTIONS',
'FBS',
'END_FBS',
'DEVICE',
'END_DEVICE',
'SYSTEM',
'END_SYSTEM',
'FUNCTION_BLOCK',
'END_FUNCTION_BLOCK',
'VAR',
'VAR_INPUT',
'VAR_OUTPUT',
'END_VAR',
'RESOURCE',
'END_RESOURCE',
'ON',
'TASK',
'WITH',
'IF',
'THEN',
'END_IF',
'ELSE',
'ELSIF',
'WHILE',
'DO',
'END_WHILE',
'BI_ADD',
'BI_MUL',
'BI_DIV',
'BI_MOD',
'BI_SUB',
'BI_GT',
'BI_GE',
'BI_EQ',
'BI_LT',
'BI_LE',
'BI_NE',
'ASM',
'END_ASM',
'LOAD',
'NISND',
'NIRCV',
'GOTO',
'STORE',
'CONST',
'IFEQ',
'CUSTOM',
'NUMBER',
'ID',
'NUMBER_REAL'
)


# Regular expression rules for simple tokens
t_TO = r'TO'
t_BI_SET_REG = r'BI_SET_REG'
t_BI_GET_REG = rBI_GET_REG
t_BI_GET_REG_REAL = r'BI_GET_REG_REAL'
t_ARROW = r'->'
t_ASSIGNMENT = r':='
t_TWO_POINTS = r':'
t_SEMICOLON = r';'
t_OP = r'('
t_CP = r')'
t_COMA = r','
t_POINT = r'.'
t_HASH = r'#'
t_OR = r'OR'
t_AND = r'AND'
t_NOT = r'NOT'
t_XOR = r'XOR'
t_GT = r'>'
t_GE = r'>='
t_LT = r'<'
t_LE = r'<='
t_EQ = r'='
t_ADD = r'+'
t_SUB = r'-'
t_MUL = r'*'
t_DIV = r'/'
t_AT = r'AT'
t_ALGORITHM = r'ALGORITHM'
t_END_ALGORITHM = r'END_ALGORITHM'
t_IN = r'IN'
t_EVENT_INPUT = r'EVENT_INPUT'
t_EVENT_OUTPUT = r'EVENT_OUTPUT'
t_END_EVENT = r'END_EVENT'
t_EC_STATES = r'EC_STATES'
t_END_STATES = r'END_STATES'
t_EC_TRANSITIONS = r'EC_TRANSITIONS'
t_END_TRANSITIONS = r'END_TRANSITIONS'
t_EVENT_CONNECTIONS = r'EVENT_CONNECTIONS'
t_DATA_CONNECTIONS = r'DATA_CONNECTIONS'
t_END_CONNECTIONS = r'END_CONNECTIONS'
t_FBS = r'FBS'
t_END_FBS = r'END_FBS'
t_DEVICE = r'DEVICE'
t_END_DEVICE = r'END_DEVICE'
t_SYSTEM = r'SYSTEM'
t_END_SYSTEM = r'END_SYSTEM'
t_FUNCTION_BLOCK = r'FUNCTION_BLOCK'
t_END_FUNCTION_BLOCK = r'END_FUNCTION_BLOCK'
t_VAR = r'VAR'
t_VAR_INPUT = r'VAR_INPUT'
t_VAR_OUTPUT = r'VAR_OUTPUT'
t_END_VAR = r'END_VAR'
t_RESOURCE = r'RESOURCE'
t_END_RESOURCE = r'END_RESOURCE'
t_ON = r'END_RESOURCE'
t_TASK = r'TASK'
t_WITH = r'WITH'
t_IF = r'IF'
t_THEN = r'THEN'
t_END_IF = r'END_IF'
t_ELSE = r'ELSE'
t_ELSIF = r'ELSIF'
t_WHILE = r'WHILE'
t_DO = r'DO'
t_END_WHILE = r'END_WHILE'
t_BI_ADD = r'ADD'
t_BI_MUL = r'MUL'
t_BI_DIV = r'DIV'
t_BI_MOD = r'MOD'
t_BI_SUB = r'SUB'
t_BI_GT = r'GT'
t_BI_GE = r'GE'
t_BI_EQ = r'EQ'
t_BI_LT = r'LT'
t_BI_LE = r'LE'
t_BI_NE = r'NE'
t_ASM = r'ASM'
t_END_ASM = r'END_ASM'
t_LOAD = r'LOAD'
t_NISND = r'NISND'
t_NIRCV = r'NIRCV'
t_GOTO = r'GOTO'
t_STORE = r'STORE'
t_CONST = r'CONST'
t_IFEQ = r'IFEQ'
t_CUSTOM = r'CUSTOM'

def t_NUMBER(t):
    r'\d+'
    t.value = int(t.value)    
    return t


