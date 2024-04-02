/**
 *@file asimov_library.h
 *@version 1.0
 *@date 22/02/2024
 *@author Grupo ASIMOV
 *@title Librería para proyecto interdisciplinar de modelización del proceso de la glucólisis en una célula
*
*/
#ifndef ASIMOV_LIBRARY_H
#define ASIMOV_LIBRARY_H
#include <QTextEdit>
#include<QString>


#endif // ASIMOV_LIBRARY_H

class TPathway;


// --------------------------------------------------------
//                     TRawInput
// --------------------------------------------------------

/**
 *@brief Definición de la clase TRawInput que implementa un tipo de dato
 *       para poder gestionar los archivos de entrada del programa.
*/
class TRawInput
{
    private:    // private members
        /**
         * @brief Variable booleana que indica si se ha cargado un archivo.
        */
        bool m_loaded;
        /**
         * @brief Variable de tipo QString en el que se guardará el contenido del archivo.
        */
        QString* m_source;

    public:
        /**
         * @brief Constructor por defecto de la clase.
         * @param v_source Apunta a nullptr por defecto.
         * @post Genera una instancia de la clase TRawInput con su contenido vacío.
        */
        TRawInput(QString* v_source = nullptr);

        /**
         * @brief Destructor de instancias de tipo TRawInput.
         *
        */
        ~TRawInput();

        //getters/setters
        /**
         * @brief Método que devuelve el contenido de una fuente.
         * @return Devuelve un QString que se corresponde con el valor de la fuente.
        */
        QString getSource();

        /**
         * @brief Método que establece el valor de la fuente.
         * @param v_source Puntero a un objeto QString que se asignará como fuente.
         * @post El objeto m_source queda apuntando al objeto QString proporcionado.
        */
        void setSource(QString* v_source);

        /**
         * @brief Método que devuelve si se ha cargado una fuente(archivo) o no.
         * @return Devuelve true en función de si m_source tiene contenido, en caso contrario devuelve false.
        */
        bool getLoaded();

        //public methods
        /**
         * @brief Intenta cargar contenido desde un archivo a m_source.
         * @details Este método verifica que m_source esté configurada y no esté vacía.
         *          Luego intenta abrir el archivo indicado por m_source en modo de solo lectura.
         *          Si la apertura del archivo es exitosa, lee su contenido y lo almacena en m_source.
         *          Finalmente, marca m_loaded como verdadero y muestra un mensaje de éxito en la consola.
         * @return Devuelve true si la carga desde el archivo fue exitosa, false en caso contrario.
        */
        bool loadFromFile();

        void setToFile();
        void Edit(QTextEdit* editor);
        void newRawInput();
        unsigned short verifyModel();
        bool createModel(TPathway& v_model);
        void clean();
};
//=========================================================


// --------------------------------------------------------
//                     TModelMetabolite
// --------------------------------------------------------

/**
 *@brief La clase TModelMetabolite implementa un tipo de dato para almacenar los
 *       metabolitos de una reacción y poder trabajar con ellos.
*/
class TModelMetabolite
{
    private:    // private members
        /**
         * @brief s_metabolites Vector estático de la clase con todos los metabolitos creados.
         */
        static std::vector<TModelMetabolite> s_metabolites;
        /**
         * @brief Nombre largo del metabolito.
         */
        QString m_name;

        /**
         * @brief Nombre corto del metabolito, es único.
         */
        QString m_id;
        /**
         * @brief Índice numérico único del metabolito.
         */
        short int m_index;
        /**
         * @brief Valor inicial del metabolito.
         * @pre Toma el valor por defecto 0.
         */
        double m_initValue;

        /**
         * @brief Valor máximo que puede alcanzar el metabolito.
         * @pre Toma el valor por defecto INT_MAX,
         */
        double m_topValue;
        /**
         * @brief Valor mínimo que puede alcanzar el metabolito.
         * @pre Toma el valor por defecto 0.
         */
        double m_bottomValue;
        /**
         * @brief Valor actual del metabolito, comienza siendo m_initValue.
         */
        double m_value;
        /**
         * @brief Precisión asociada a los valores del metabolito.
         * @pre Toma el valor por defecto 0.0000001.
         */
        double m_precision;
        /**
         * @brief Etiqueta del metabolito.
         * @pre Toma el valor por defecto false.
         */
        bool m_tag;

    public:
        /**
         * @brief TModelMetabolite Constructor de la clase, crea un objeto metabolito válido
         *        con los parámetros proporcionados.
         * @param m_index Índice numérico único del metabolito.
         * @param m_name Nombre largo del metabolito.
         * @param m_id Nombre corto del metabolito, único.
         * @param m_initValue Valor inicial del metabolito.
         * @param m_topValue Valor máximo que puede alcanzar el metabolito.
         * @param m_bottomValue Valor mínimo que puede alcanzar el metabolito.
         * @param m_value Valor actual del metabolito.
         * @param m_precision Precisión asociada al valor del metabolito.
         * @param m_tag Etiqueta asociada al metabolito.
         */
        TModelMetabolite(short int m_index, QString m_name, QString m_id, double m_initValue, double m_topValue,
                         double m_bottomValue, double m_value, double m_precision, bool m_tag);

        /**
         * @brief check Comprueba la consistencia de los datos recogidos del metabolito.
         * @return true si los datos son válidos, false en caso contrario.
         */
        bool check();

        // getters/setters
        /**
         * @brief getName devuelve el nombre largo del metabolito.
         * @return atributo m_name.
         */
        QString getName();

        /**
         * @brief getId devuelve el nombre corto del metabolito.
         * @return atributo m_id.
         */
        QString getId();

        /**
         * @brief getIndex devuelve el índice numérico asociado al metabolito.
         * @return atributo m_index.
         */
        short int getIndex();

        /**
         * @brief getInitValue devuelve el valor inicial del metabolito.
         * @return atributo m_initValue.
         */
        double getInitValue();

        /**
         * @brief getTopValue devuelve el valor máximo que puede alcanzar el metabolito.
         * @return atributo m_topValue.
         */
        double getTopValue();

        /**
         * @brief getBottomValue devuelve el valor mínimo que puede alcanzar el metabolito.
         * @return atributo m_bottomValue.
         */
        double getBottomValue();

        /**
         * @brief getValue devuelve el valor actual del metabolito.
         * @return atributo m_value.
         */
        double getValue();

        /**
         * @brief getPrecision devuelve la precisión asociada al metabolito.
         * @return atributo m_precision.
         */
        double getPrecision();

        /**
         * @brief getTag devuelve la etiqueta que tiene el metabolito.
         * @return atributo m_tag.
         */
        bool getTag();

        /**
         * @brief setValue modifica el valor actual del metabolito.
         * @param v_value nuevo valor del metabolito.
         */
        void setValue(double v_value);

        /**
         * @brief setTag modifica la etiqueta del metabolito.
         * @param v_tag nueva etiqueta.
         */
        void setTag(bool v_tag);

        /**
         * @brief range calcula el rango de valores del metabolito.
         * @return double resultante de restar (m_topValue - m_bottomValue).
         */
        double range();

        friend class TProcess;
};
//=========================================================


// --------------------------------------------------------
//                     TModelParameter
// --------------------------------------------------------

/**
 *@brief Esta clase encapsula información sobre un parámetro y se usa para representar
 *       y manipular parámetros específicos relacionados con la glucólisis.
*/
class TModelParameter
{
    private:    // private members
        /**
         * @brief s_params Vector estático de la clase con todos los parámetros creados.
         */
        static std::vector<TModelParameter> s_params;
        /**
         *@brief Índice del parámetro.
        */
        short int m_index;
        /**
         *@brief Identificación única para el parámetro.
        */
        QString m_id;
        /**
         *@brief Decripción del parámetro.
        */
        QString m_description;
        /**
         *@brief Valor numértico del parámetro.
        */
        double m_value;
        /**
         *@brief Precición asociada al valor del parámetro.
        */
        double m_precision;
        /**
         *@brief Etiqueta para marcar en caso de que queramos hacer un uso específico de ese parámetro.
        */
        bool m_tag;

    public:

        /**
         * @brief TModelParameter constructor de la clase, crea un objeto parámetro válido.
         * @param m_index índice numérico único del parámetro.
         * @param m_ID nombre corto del parámetro, es único.
         * @param m_Description nombre largo del parámetro.
         * @param m_Value valor actual del parámetro.
         * @param m_Precision precisión asociada al parámetro.
         * @param m_Tag etiqueta asociada al parámetro.
         */
        TModelParameter(short int m_index, QString m_ID, QString m_Description, double m_Value,double m_Precision, bool m_Tag);

        /**
         * @brief check Comprueba la consistencia de los datos recogidos del parámetro.
         * @return true si los datos son válidos, false en caso contrario.
         */
        bool check();

        /**
         * @brief getIndex devuelve el índice numérico del parámetro.
         * @return variable estática s_counter.
         */
        short int getIndex();

        /**
         * @brief getId devuelve el nombre corto del parámetro.
         * @return atributo m_id.
         */
        QString getId();

        /**
         * @brief getDescription devuelve el nombre largo del parámetro.
         * @return atributo m_description.
         */
        QString getDescription();

        /**
         * @brief getValue devuelve el valor actual del parámetro.
         * @return atributo m_value.
         */
        double getValue();

        /**
         * @brief getPrecision devuelve la precisión asociada al parámetro.
         * @return atributo m_precision.
         */
        double getPrecision();

        /**
         * @brief getTag devuelve la etiqueta asociada al parámetro.
         * @return atributo m_tag.
         */
        bool getTag();

        /**
         * @brief setTag modifica el valor actual de la etiqueta.
         * @param v_tag valor nuevo de etiqueta para el parámetro.
         */
        void setTag(bool v_tag);

        /**
         * @brief setValue modifica el valor actual del parámetro.
         * @param v_value valor nuevo del parámetro.
         */
        void setValue(double v_value);

        friend class TProcess;
};
//=========================================================


// --------------------------------------------------------
//                    TFormalism
// --------------------------------------------------------

class TFormalism
{
    private:
        /**
         * @brief s_formalisms Vector con todos los formalismos creados.
         *        Su posición en el vector coincide con su id.
         */
        static std::vector<TFormalism> s_formalisms;

        /**
         * @brief m_id Identificador del formalismo.
         */
        QString m_id;

        /**
         * @brief m_name Nombre bioquímico del formalismo.
         */
        QString m_name;

        /**
         * @brief m_formalism Cadena de caracteres que representa la ecuación del formalismo.
         */
        QString m_formalism;

        /**
         * @brief m_variables Vector de nombres de variables que aparecen en el formalismo.
         */
        std::vector<QString> m_variables;

    public:
        /**
         * @brief TFormalism Constructor de la clase TFormalism. Crea un objeto formalismo válido.
         * @param m_id Identificador del formalismo.
         * @param m_name Nombre largo del formalismo.
         * @param m_formalism Ecuación del formalismo.
         * @param m_variables Vector de nombres de variables que aparecen en la ecuación.
         */
        TFormalism(QString m_id, QString m_name, QString m_formalism, std::vector<QString> m_variables);

        /**
         * @brief check Método que comprueba la consistencia entre las variables y la ecuación
         *        proporcionadas. En el formalismo deben aparecer todas las variables proporcionadas
         *        y sólo esas. Es llamado dentro del constructor antes de crear el objeto.
         * @return true si los datos del formalismo son correctos, false en caso contrario.
         */
        bool check();

        /**
         * @brief getId Devuelve el identificador del formalismo.
         * @return devuelve el QString m_id
         */
        QString getId();

        /**
         * @brief getName Devuelve el nombre del formalismo.
         * @return devuelve el QString m_name
         */
        QString getName();

        /**
         * @brief getFormalism Devuelve la ecuación del formalismo.
         * @return devuelve el QString m_formalism
         */
        QString getFormalism();

        /**
         * @brief getVariables Devuelve una lista de las variables que participan
         * @return devuelve lista de variables
         */
        QString getVariables();

        /**
         * @brief Clase amiga que puede acceder a los datos privados de TFormalism.
         */
        friend class TProcess;

};
//=========================================================


// --------------------------------------------------------
//                    TProcess
// --------------------------------------------------------

class TProcess
{
    private:
        /**
         * @brief s_processes Vector con todos los procesos creados.
         *        Su posición en el vector coincide con su id.
         */
        static std::vector<TProcess> s_processes;

        /**
         * @brief m_id Identificador del proceso.
         */
        QString m_id;

        /**
         * @brief m_name Nombre corto del proceso.
         */
        QString m_name;

        /**
         * @brief m_description Nombre bioquímico del proceso.
         */
        QString m_description;

        /**
         * @brief m_idForm Identificador del formalismo al que hace referencia.
         */
        QString m_idForm;

        /**
         * @brief m_substances Vector de identificadores de las sustancias (metanodos y parámetros)
         *        que aparecen en el proceso.
         */
        std::vector<QString> m_substances;

    public:

        /**
         * @brief TProcess Constructor de la clase TProcess. Crea un proceso válido.
         * @param m_id Identificador del proceso.
         * @param m_name Nombre corto del proceso.
         * @param m_description Nombre bioquímico del proceso.
         * @param m_idForm Identificador del formalismo que usa.
         * @param m_substances Vector de las sustancias que aparecen en el proceso.
         */
        TProcess(QString m_id, QString m_name, QString m_description, QString m_idForm, std::vector<QString> m_substances);

        /**
         * @brief check Método que comprueba la consistencia de los datos del proceso recogidos.
         *        El formalismo y las variables (metanodos y parámetros) recogidas deben existir.
         *        Se llama dentro del constructor, para crear un objeto Proceso válido.
         * @return true si los datos del proceso son correctos, false en caso contrario.
         */
        bool check();

        /**
         * @brief getFormalism Método que devuelve el objeto formalismo asociado al proceso.
         * @param QString Identificador del formalismo asociado al proceso.
         * @return Objeto TFormalismo asociado al proceso.
         */
        TFormalism getFormalism(QString m_idForm);

        /**
         * @brief getProcess Método que construye la ecuación del proceso basada en el formalismo y las
         *        variables del objeto Proceso que lo llama.
         * @return Cadena de caracteres con la ecuación del proceso, donde las variables son las especificadas.
         */
        QString getProcess();
};
//=========================================================






// --------------------------------------------------------
//                    TModelReaction
// --------------------------------------------------------

/**
 * @brief La clase TModelReaction encapsula la información necesaria
 *        para gestionar una reacción metabólica.
 */

class TModelReaction
{
    private:    // private members

        /**
         * @brief s_counter Contador numérico del número de reacciones almacenadas.
         *        Se actualiza en el constructor de la clase, sumando uno con cada
         *        reacción creada.
         */
        static short int s_counter;

        QString m_id;
        QString m_description;
        std::vector<int> m_reagent;
        std::vector<int> m_product;
        std::vector<int> m_parameter;
        QString m_equation;
        bool m_tag;

    public:     // constructors
        TModelReaction(short int v_Index = -1, QString v_ID = "",
                       QString v_Description = "", std::vector<int> v_Reagent= { 0 },
                       std::vector<int> v_Product = { 0 },
                       std::vector<int> v_Parameter= { 0 }, QString v_Equation= "",
                       bool v_Tag = false);

    public:     // getters/setters
        short int getIndex();
        void setIndex(short int v_index);
        QString getId();
        void setid(QString v_id);
        QString getDescription();
        void setDescription(QString v_description);
        std::vector<int> getAllReagents();
        void setAllReagents(std::vector<int> v_reagents);
        std::vector<int> getAllProducts();
        void setAllProducts(std::vector<int> v_products);
        std::vector<int> getAllParameters();
        void setAllParameters(std::vector<int> v_parameters);
        int GetReagentNo ();
        void SetReagentNo(std::vector<int>(int i));
        int GetProductNo ();
        void SetProductNo(std::vector<int>(int i));
        int GetOarameterNo ();
        void SetParameterNo(std::vector<int>(int i));
        QString getEquation();
        void setEquation(QString v_equation);
        bool getTag();
        void setTag(bool v_tag);

    public:     //public methods
        int ReagentsCount();
        int ProductsCount();
        int ParametersCount();
        TModelMetabolite &Reagent(const int index);
        TModelMetabolite &Product(const int index);
        TModelMetabolite &Parameter(const int index);

};


// --------------------------------------------------------
//                     TRunConfig
// --------------------------------------------------------


class TRunConfig
{
    private:    // private members
        double m_initTime;
        double m_endTime;
        size_t m_cycles;
        QString m_paramList;


    public:     // constructors
        TRunConfig(double v_initTime = 0, double v_endTime    = 0,
                   size_t v_cycles   = 0, QString v_paramList = ""):
                   m_initTime(v_initTime), m_endTime (v_endTime),
                   m_cycles (v_cycles), m_paramList (v_paramList){};

    public:     // getters/setters
        double getInitTime();
        void setInitTime(double t);
        double getEndTime();
        void setEndTime(double t);
        size_t getCycles();
        void setCycles(size_t value);
        QString getParamList();
        void setParamList(QString pList);


    public:     //public methods

};


// --------------------------------------------------------
//                     TFrameData
// --------------------------------------------------------


class TFrameData
{
private:    // private members

public:     // constructors

public:     // getters/setters

public:     //public methods

};


// --------------------------------------------------------
//                     TPathway
// --------------------------------------------------------


class TPathway
{
private:    // private members

public:     // constructors

public:     // getters/setters

public:     //public methods

};


