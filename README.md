# Sistema de Hospital

Sistema de gerenciamento hospitalar desenvolvido em C, utilizando ponteiros e conceitos fundamentais de programação estruturada.

O projeto foi criado com fins acadêmicos, com o objetivo de praticar manipulação de memória, estruturas de dados e organização de código em linguagem C.

---

## Sobre o Projeto

O sistema permite realizar o gerenciamento básico de um hospital através de um menu interativo no terminal.

Nele é possível cadastrar pacientes, médicos e consultas, além de buscar, listar e excluir registros.

O foco principal do projeto é demonstrar o uso de:

- Ponteiros
- Structs
- Alocação dinâmica de memória
- Modularização em C
- Organização de arquivos `.c` e `.h`
- Programação estruturada

---

## Funcionalidades

### Pacientes
- Cadastro de pacientes
- Listagem de pacientes
- Busca por CPF
- Exclusão de pacientes

### Médicos
- Cadastro de médicos
- Listagem de médicos
- Busca por CRM
- Exclusão de médicos

### Consultas
- Registro de consultas
- Associação entre paciente e médico
- Visualização de consultas cadastradas

---

## Tecnologias Utilizadas

- Linguagem C
- Ponteiros
- Structs
- Manipulação dinâmica de memória
- Modularização de código
- GCC

---

## Estrutura do Projeto

```bash
Sistema-de-Hospital/
│
├── main.c             # Arquivo principal
├── paciente.c         # Funções relacionadas aos pacientes
├── medico.c           # Funções relacionadas aos médicos
├── consulta.c         # Funções relacionadas às consultas
├── utils.c            # Funções auxiliares
├── *.h                # Arquivos de cabeçalho
└── README.md          # Documentação do projeto
```

---

## Como Executar

### 1. Clone o repositório

```bash
git clone https://github.com/Hudson-Nasciment0/Sistema-de-Hospital.git
```

### 2. Entre na branch do projeto

```bash
git checkout Ponteiro
```

### 3. Compile o projeto

```bash
gcc *.c -o hospital
```

### 4. Execute o sistema

#### Linux / MacOS
```bash
./hospital
```

#### Windows
```bash
hospital.exe
```

---

## Objetivos Acadêmicos

Este projeto foi desenvolvido para reforçar conceitos importantes da disciplina de programação, especialmente:

- Manipulação de ponteiros
- Organização de sistemas maiores em C
- Separação de responsabilidades no código
- Uso de memória dinâmica
- Desenvolvimento em equipe utilizando Git e GitHub

---

## Aprendizados

Durante o desenvolvimento, foram praticados conceitos como:

- Criação e manipulação de structs
- Passagem de parâmetros por referência
- Modularização
- Organização lógica do sistema
- Trabalho colaborativo em repositórios Git

---

## Autores

- Beatriz Barboza Marques Lima da Silva
- Davy Queiroz da Silva
- Hudson Nascimento Pereira Vieira
- Igor dos Santos Moura
- Matheus Lima Rocha
- Rafael dos Santos Paulo
- Rodrigo Gomes da Conceição

---

## Repositório

https://github.com/Hudson-Nasciment0/Sistema-de-Hospital
