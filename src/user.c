#include "user.h"

int criarMenuLogin()
{
    char entrada;
    printf("**LOCADORA VIRTUAL**\n\n1.Login\n2.Cadastro\n3.Sair\n");
    scanf("%c", &entrada);

    switch (entrada)
    {
    case '1':

        return realizarLogin();

        break;
    case '2':

        if (realizarCadastro())
        {
            return realizarLogin();
        }
        else
        {
            return 0;
        }
        break;
    case '3':
        return 2;
        break;
    case '4':

        break;

    default:
        break;
    }

    // system("clear");
    return 0;
}

Usuario *carregarUsuarios()
{

    Usuario *user;
    user = (Usuario *)malloc(sizeof(Usuario) * TAM);
    int countUsuario = 0;
    qtdUsuarios = 0;

    FILE *file = fopen("data/usuarios.csv", "r");

    char linha[1024];

    while (fgets(linha, 1024, file))
    {

        strcpy(user[countUsuario].nome, strtok(linha, ","));
        strcpy(user[countUsuario].senha, strtok(NULL, ","));

        // printf("1:%s, ", user[countUsuario].nome);
        // printf("2:%s\n", user[countUsuario].senha);

        qtdUsuarios++;
        countUsuario++;
    };

    fclose(file);

    return user;
}

int realizarLogin()
{

    Usuario *usuarios = carregarUsuarios();

    char nome[TAM];
    char senha[TAM];
    system("clear");

    printf("Usuario: ");
    scanf("%s", nome);
    printf("\nSenha: ");
    scanf("%s", senha);

    for (int i = 0; i < qtdUsuarios; i++)
    {
        if (!strcmp(nome, usuarios[i].nome)) // verifica se há um usuario com o que foi digitado
        {
            // printf("%s - %s\n", nome, usuarios[i].nome);
            // printf("%s - %s", senha, usuarios[i].senha);
            usuarios[i].senha[strcspn(usuarios[i].senha, "\n")] = 0; // Toma como nulo a posição da string que ocorrer um "\n"

            if (!strcmp(senha, usuarios[i].senha)) // verifica se a senha do usuario confere.
            {
                system("clear");
                free(usuarios);
                return 1;
            }
            else
            {
                system("clear");
                printf("\nSenha incorreta. ");
                free(usuarios);
                return 0;
            }
        }
    }
    system("clear");
    printf("\nUsuario nao cadastrado.");

    free(usuarios);
    return 0;
}

int realizarCadastro()
{
    Usuario novoUsuario;

    Usuario *usuarios = carregarUsuarios();
    char confSenha[30];

    printf("Digite seu nome de usuario: ");
    scanf("%s", novoUsuario.nome);
    printf("\nDigite sua senha: ");
    scanf("%s", novoUsuario.senha);
    printf("\nConfirme sua senha: ");
    scanf("%s", confSenha);

    for (int i = 0; i < qtdUsuarios; i++)
    {

        if (!strcmp(novoUsuario.nome, usuarios[i].nome)) // verifica se há um usuario com o que foi digitado
        {
            system("clear");
            printf("\nNome de usuario já utilizado.");
            return 0;
        }
    }

    if (!strcmp(confSenha, novoUsuario.senha))
    {
        FILE *file = fopen("data/usuarios.csv", "a");

        fprintf(file, "\n%s,%s", novoUsuario.nome, novoUsuario.senha);
        qtdUsuarios++;

        fclose(file);

        printf("\n Usuario cadastrado com sucesso!\n \n Pressione enter para continuar!");
        getchar(); 
        return 1;
    }
}