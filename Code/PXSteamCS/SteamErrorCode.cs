namespace PX
{
	public enum SteamErrorCode
	{
		Invalid,
		Success,

		InvalidImageSize,
		NoImage,
		ImageLoadFailed,
		InputBufferTooSmal
	}













    public class DataBase
    {
		private static DataBase _instance;

		public static DataBase Instace()
        {
            if (_instance == null)
            {
				_instance = new DataBase();

			}

			return _instance;
		}

		private DataBase()
        {
			
        }
	}

	void main()
    {

		DataBase dataBase = DataBase.Instace();
		

	}

}